#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>
#include <vector>

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
    virtual int insertUser(const std::string &login, const std::string &password) = 0;
    virtual bool getUserId(const std::string &login, int &result) = 0;
    virtual bool getUserPassword(const int id, std::string &result) = 0;
    virtual bool getUserData(const std::string &ids, std::string &result) = 0;
    virtual bool getAllUsersData(std::vector<std::tuple<std::string, std::string> > &result) = 0;
};

#endif // IDATABASE_H
