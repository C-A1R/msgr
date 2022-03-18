#ifndef ISERVERPROCESSOR_H
#define ISERVERPROCESSOR_H

#include <string>

/**
 * @brief интерфейс обработчика запросов/ответов от клиента
 */
class IServerProcessor
{
public:
    IServerProcessor() = default;
    virtual ~IServerProcessor() = default;

    virtual std::string parseClientMessage(const std::string &request) = 0;
};

#endif // ISERVERPROCESSOR_H
