#ifndef SERVERPROCESSOR_H
#define SERVERPROCESSOR_H

#include "IServerProcessor.h"
#include "../Database.h"

#include <memory>

class ServerProcessor : public IServerProcessor
{
    std::shared_ptr<Database> _db;
public:
    ServerProcessor(const std::shared_ptr<Database> &db);

    std::string getResponse(const std::string &request) override;

private:
//    void parseRequest(const std::string &request);
};

#endif // SERVERPROCESSOR_H
