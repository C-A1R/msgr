#ifndef USERINFO_H
#define USERINFO_H

#include <string>

struct UserInfo
{
    int id{-1};
    std::string login;
    std::string name;
    UserInfo() = default;
    std::string username() const { return name.empty() ? login : name; }
};

#endif // USERINFO_H
