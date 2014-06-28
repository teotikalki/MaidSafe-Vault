/*  Copyright 2012 MaidSafe.net limited

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

#include "maidsafe/vault/vault.h"

#include <functional>
#include <memory>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

#include "maidsafe/common/test.h"
#include "maidsafe/common/utils.h"
#include "maidsafe/passport/passport.h"

namespace maidsafe {

namespace vault {

namespace test {

class VaultTest : public testing::Test {
 public:
  VaultTest()
      : kTestRoot_(maidsafe::test::CreateTestPath("MaidSafe_Test_Vault")),
        vault_root_directory_(*kTestRoot_ / RandomAlphaNumericString(8)),
        pmid_(passport::CreatePmidAndSigner().first),
        on_new_bootstrap_endpoint_([](boost::asio::ip::udp::endpoint /*endpoint*/) {}),
        vault_() {
    boost::filesystem::create_directory(vault_root_directory_);
  }

 protected:
  const maidsafe::test::TestPath kTestRoot_;
  boost::filesystem::path vault_root_directory_;
  passport::Pmid pmid_;
  std::function<void(boost::asio::ip::udp::endpoint)> on_new_bootstrap_endpoint_;
  std::unique_ptr<Vault> vault_;
};

TEST_F(VaultTest, BEH_Constructor) {
  std::vector<passport::PublicPmid> public_pmids_from_file;
  public_pmids_from_file.push_back(passport::PublicPmid(passport::CreatePmidAndSigner().first));
  routing::BootstrapContacts bootstrap_contacts;
  bootstrap_contacts.push_back(boost::asio::ip::udp::endpoint(GetLocalIp(),
                                                          (RandomUint32() % 64511) + 2025));
  vault_manager::VaultConfig vault_config(pmid_, vault_root_directory_, DiskUsage(1000000000),
                                          bootstrap_contacts);
  vault_config.test_config.public_pmid_list = public_pmids_from_file;
  EXPECT_THROW(vault_.reset(new Vault(vault_config, on_new_bootstrap_endpoint_)),
               vault_error);  // throws VaultErrors::failed_to_join_network
}

}  // namespace test

}  // namespace vault

}  // namespace maidsafe
