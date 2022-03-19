#include "SqlRec.h"

void SqlRec::insert(const std::string &field, const std::string &value)
{
    values.insert(std::make_pair(field, value));
}

std::string SqlRec::value(const std::string &field) const
{
    if (!values.count(field))
        return std::string();
    return values.at(field);
}
