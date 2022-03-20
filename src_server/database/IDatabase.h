#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>
#include <vector>

class UserInfo;
class MessageInfo;

/**
 * @brief через этот класс происходит работа с базой
 */
class IDatabase
{
public:
    IDatabase() = default;
    virtual ~IDatabase() = default;

    virtual bool create() = 0;
    virtual bool open() = 0;
    virtual int invalidId() const = 0;
    virtual int insertUser(const std::pair<std::string, std::string> &values) = 0;
    virtual bool getUserId(const std::string &login, int &result) = 0;
    virtual bool getUserPassword(const int id, std::string &result) = 0;
    virtual bool getUsername(const int id, std::string &result) = 0;
    virtual bool getAllUsers(std::vector<UserInfo> &result) = 0;
    virtual int insertMessage(int sender, int recipient, const std::string &text) = 0;
    virtual bool getMessages(int user_1, int user_2, int lastId, std::vector<MessageInfo> &result) = 0;
};

#endif // IDATABASE_H
