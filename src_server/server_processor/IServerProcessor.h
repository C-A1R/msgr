#ifndef ISERVERPROCESSOR_H
#define ISERVERPROCESSOR_H

#include <string>

class IServerProcessor
{
public:
    IServerProcessor() = default;
    virtual ~IServerProcessor() = default;

    virtual std::string getResponse(const std::string &request) = 0;
};

#endif // ISERVERPROCESSOR_H
