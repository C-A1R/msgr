#ifndef SERVERPROCESSOR_H
#define SERVERPROCESSOR_H

#include "IServerProcessor.h"
#include "../database/Database.h"

#include <boost/property_tree/ptree.hpp>

#include <memory>

class ServerProcessor : public IServerProcessor
{
    std::shared_ptr<IDatabase> _db;
    const std::string errResponse = "{\n    \"response_type\": \"error\"\n}\n";
public:
    ServerProcessor(const std::shared_ptr<IDatabase> &db);

    std::string getResponse(const std::string &request) override;

private:
    std::string signUpResponse(const boost::property_tree::ptree &requestRoot);
    std::string signInResponse(const boost::property_tree::ptree &requestRoot);
    std::string outputMessageResponse(const boost::property_tree::ptree &requestRoot);
};

#endif // SERVERPROCESSOR_H
