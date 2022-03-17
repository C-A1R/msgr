#include "ServerProcessor.h"

#include <boost/property_tree/json_parser.hpp>

#include <iostream>

ServerProcessor::ServerProcessor(const std::shared_ptr<IDatabase> &db)
    : _db{db}
{
}

std::string ServerProcessor::getResponse(const std::string &request)
{
    if (request == "ping\n")
    {
        return "pong\n";
    }

    std::stringstream requestStream(request);
    boost::property_tree::ptree requestRoot;
    boost::property_tree::read_json(requestStream, requestRoot);

    std::string requestType = requestRoot.get<std::string>("request_type");
    if (requestType == "sign_up")
    {
        return signUpResponse(requestRoot);
    }
    else if (requestType == "sign_in")
    {
        return signInResponse(requestRoot);
    }

    return errResponse;
}

std::string ServerProcessor::signUpResponse(const boost::property_tree::ptree &requestRoot)
{
    auto login = requestRoot.get<std::string>("user.login");
    auto password = requestRoot.get<std::string>("user.password");
    int userId = _db->invalidId();
    _db->getUserId(login, userId);
    if (userId != _db->invalidId())
    {
        //логин занят
        boost::property_tree::ptree responseRoot;
        responseRoot.put("response_type", "sign_up");
        responseRoot.put("status", "login_exists");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    userId = _db->insertUser(login, password);
    if (userId != _db->invalidId())
    {
        boost::property_tree::ptree responseRoot;
        responseRoot.put("response_type", "sign_up");
        responseRoot.put("status", "ok");
        responseRoot.put("user.id", userId);
        responseRoot.put("user.login", login);

        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }
    return errResponse;
}

std::string ServerProcessor::signInResponse(const boost::property_tree::ptree &requestRoot)
{
    auto login = requestRoot.get<std::string>("user.login");
    auto password = requestRoot.get<std::string>("user.password");
    int userId = _db->invalidId();

    _db->getUserId(login, userId);
    if (userId == _db->invalidId())
    {
        boost::property_tree::ptree responseRoot;
        responseRoot.put("response_type", "sign_in");
        responseRoot.put("status", "login_not_exists");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    std::string realPassword;
    _db->getUserPassword(userId, realPassword);
    if (password != realPassword)
    {
        boost::property_tree::ptree responseRoot;
        responseRoot.put("response_type", "sign_in");
        responseRoot.put("status", "password_incorrect");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    boost::property_tree::ptree responseRoot;
    responseRoot.put("response_type", "sign_in");
    responseRoot.put("status", "ok");
    responseRoot.put("user.id", userId);
    responseRoot.put("user.login", login);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    return responseStream.str() + "\n";
}
