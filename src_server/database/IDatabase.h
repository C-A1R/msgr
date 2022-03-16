#ifndef IDATABASE_H
#define IDATABASE_H

#include <string>

class IDatabase
{
public:
    IDatabase() = default;
    virtual ~IDatabase() = default;

    virtual std::string ok() const = 0;

    virtual bool create() = 0;
    virtual bool open() = 0;
    virtual int invalidId() const = 0;
    virtual int insertUser(const std::string &login, const std::string &password) = 0;
};

#endif // IDATABASE_H
