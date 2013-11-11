/*  Copyright 2013 MaidSafe.net limited

    This MaidSafe Software is licensed to you under (1) the MaidSafe.net Commercial License,
    version 1.0 or later, or (2) The General Public License (GPL), version 3, depending on which
    licence you accepted on initial access to the Software (the "Licences").

    By contributing code to the MaidSafe Software, or to this project generally, you agree to be
    bound by the terms of the MaidSafe Contributor Agreement, version 1.0, found in the root
    directory of this project at LICENSE, COPYING and CONTRIBUTOR respectively and also
    available at: http://www.maidsafe.net/licenses

    Unless required by applicable law or agreed to in writing, the MaidSafe Software distributed
    under the GPL Licence is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
    OF ANY KIND, either express or implied.

    See the Licences for the specific language governing permissions and limitations relating to
    use of the MaidSafe Software.                                                                 */

#include "maidsafe/vault/pmid_manager/action_set_available_size.h"
#include "maidsafe/vault/pmid_manager/action_set_available_size.pb.h"

#include "maidsafe/vault/pmid_manager/value.h"
#include "maidsafe/vault/pmid_manager/metadata.h"

namespace maidsafe {

namespace vault {

ActionPmidManagerSetAvailableSize::ActionPmidManagerSetAvailableSize(
    const int64_t& disk_available_size) : kDiskAvailableSize(disk_available_size) {}

ActionPmidManagerSetAvailableSize::ActionPmidManagerSetAvailableSize(
    const std::string& serialised_action)
        : kDiskAvailableSize([&serialised_action]() {
                               protobuf::ActionPmidManagerSetAvailableSize action_disk_size_proto;
                               if (!action_disk_size_proto.ParseFromString(serialised_action))
                                 ThrowError(CommonErrors::parsing_error);
                               return action_disk_size_proto.disk_available_size();
                             }()) {}

ActionPmidManagerSetAvailableSize::ActionPmidManagerSetAvailableSize(
    const ActionPmidManagerSetAvailableSize& other)
        : kDiskAvailableSize(other.kDiskAvailableSize) {}

ActionPmidManagerSetAvailableSize::ActionPmidManagerSetAvailableSize(
    ActionPmidManagerSetAvailableSize&& other)
        : kDiskAvailableSize(std::move(other.kDiskAvailableSize)) {}

std::string ActionPmidManagerSetAvailableSize::Serialise() const {
  protobuf::ActionPmidManagerSetAvailableSize action_disk_size_proto;
  action_disk_size_proto.set_disk_available_size(kDiskAvailableSize);
  return action_disk_size_proto.SerializeAsString();
}

detail::DbAction ActionPmidManagerSetAvailableSize::operator()(PmidManagerMetadata& metadata) {
  metadata.SetAvailableSize(kDiskAvailableSize);
  return detail::DbAction::kPut;
}

bool operator==(const ActionPmidManagerSetAvailableSize& /*lhs*/,
                const ActionPmidManagerSetAvailableSize& /*rhs*/) {
  return true;
}

bool operator!=(const ActionPmidManagerSetAvailableSize& lhs,
                const ActionPmidManagerSetAvailableSize& rhs) {
  return !operator==(lhs, rhs);
}

}  // namespace vault

}  // namespace maidsafe
