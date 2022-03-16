#ifndef SERVERPROCESSOR_H
#define SERVERPROCESSOR_H

#include "IServerProcessor.h"
#include "../database/Database.h"

#include <memory>

class ServerProcessor : public IServerProcessor
{
    std::shared_ptr<IDatabase> _db;
public:
    ServerProcessor(const std::shared_ptr<IDatabase> &db);

    std::string getResponse(const std::string &request) override;

private:
//    void parseRequest(const std::string &request);
};

#endif // SERVERPROCESSOR_H
