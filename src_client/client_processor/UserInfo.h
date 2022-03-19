#ifndef USERINFO_H
#define USERINFO_H

#include <QMetaType>

#include <string>

struct UserInfo
{
    int id{-1};
    std::string login;
    UserInfo() = default;
    UserInfo(int id, const std::string &login) : id{id}, login{login} {}
};

Q_DECLARE_METATYPE(std::vector<UserInfo>)

#endif // USERINFO_H
