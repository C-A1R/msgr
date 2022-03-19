#ifndef SQLREC_H
#define SQLREC_H

#include <unordered_map>

class SqlRec
{
    std::unordered_map<std::string, std::string> values;
public:
    SqlRec() = default;
    void insert(const std::string &field, const std::string &value);
    std::string value(const std::string &field) const;
};

#endif // SQLREC_H
