#include "Login.h"

Login::Login() {
    adminAccounts.push_back({"sugeng", "sugeng123"});
    adminAccounts.push_back({"geren", "geren123"});
}

void Login::addAdmin(const std::string &user, const std::string &pass) {
    adminAccounts.push_back({user, pass});
}

bool Login::authenticateAdmin(const std::string &username, const std::string &password) const {
    for (const auto &acc : adminAccounts) {
        if (acc.first == username && acc.second == password) return true;
    }
    return false;
}
