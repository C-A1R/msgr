#include "ServerProcessor.h"

#include <iostream>

ServerProcessor::ServerProcessor(const std::shared_ptr<Database> &db)
    : _db{db}
{
}

std::string ServerProcessor::getResponse(const std::string &request)
{
    if (request == "ping\n")
    {
        return "pong\n";
    }
    else
    {
        std::cout << "# user: " << _db->insertUser("login", "password") << std::endl;
        return request;
    }
}
