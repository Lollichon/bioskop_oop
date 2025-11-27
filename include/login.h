#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <vector>

class Login {
private:
    std::vector<std::pair<std::string, std::string>> adminAccounts;

public:
    Login();

    void addAdmin(const std::string &user, const std::string &pass);
    bool authenticateAdmin(const std::string &username, const std::string &password) const;
};

#endif // LOGIN_H
