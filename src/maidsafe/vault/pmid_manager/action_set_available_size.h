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

#ifndef MAIDSAFE_VAULT_PMID_MANAGER_ACTION_SET_AVAILABLE_SIZE_H_
#define MAIDSAFE_VAULT_PMID_MANAGER_ACTION_SET_AVAILABLE_SIZE_H_

#include <string>

#include "boost/optional/optional.hpp"

#include "maidsafe/common/error.h"
#include "maidsafe/common/log.h"

#include "maidsafe/vault/config.h"
#include "maidsafe/vault/pmid_manager/pmid_manager.h"

#include "maidsafe/vault/pmid_manager/value.h"
#include "maidsafe/vault/pmid_manager/metadata.h"

namespace maidsafe {

namespace vault {

struct ActionPmidManagerSetAvailableSize {
  ActionPmidManagerSetAvailableSize(const int64_t& disk_available_size);
  explicit ActionPmidManagerSetAvailableSize(const std::string& serialised_action);
  ActionPmidManagerSetAvailableSize(const ActionPmidManagerSetAvailableSize& other);
  ActionPmidManagerSetAvailableSize(ActionPmidManagerSetAvailableSize&& other);

  detail::DbAction operator()(PmidManagerMetadata& metadata);

  std::string Serialise() const;

  static const nfs::MessageAction kActionId = nfs::MessageAction::kCreateAccountRequest;

 private:
  ActionPmidManagerSetAvailableSize& operator=(ActionPmidManagerSetAvailableSize other);

  int64_t kDiskAvailableSize;
};

bool operator==(const ActionPmidManagerSetAvailableSize& lhs,
                const ActionPmidManagerSetAvailableSize& rhs);
bool operator!=(const ActionPmidManagerSetAvailableSize& lhs,
                const ActionPmidManagerSetAvailableSize& rhs);

}  // namespace vault

}  // namespace maidsafe

#endif  // MAIDSAFE_VAULT_PMID_MANAGER_ACTION_SET_AVAILABLE_SIZE_H_
