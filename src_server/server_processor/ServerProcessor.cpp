#include "ServerProcessor.h"
#include "../Session.h"
#include "../SessionManager.h"

#include <boost/property_tree/json_parser.hpp>

#include <iostream>

ServerProcessor::ServerProcessor(const std::shared_ptr<IDatabase> &db,
                                 const std::shared_ptr<SessionManager> &sessionMgr,
                                 const std::shared_ptr<Session> &currentSession)
    : _db{db}, _sessionMgr{sessionMgr}, _currentSession{currentSession}
{
}

std::string ServerProcessor::parseClientMessage(const std::string &msg)
{
    std::cout << msg;
    if (msg == "ping\n")
    {
        return "pong\n";
    }

    std::stringstream stream(msg);
    ptree root;
    boost::property_tree::read_json(stream, root);

    if (root.count("request_type") > 0)
    {
        return parseRequest(root);
    }
    else if (root.count("response_type") > 0)
    {
        return parseResponse(root);
    }
    return std::string();
}

std::string ServerProcessor::parseRequest(const ptree &root)
{
    std::string requestType = root.get<std::string>("request_type");
    if (requestType == "sign_up")
    {
        return signUp(root);
    }
    else if (requestType == "sign_in")
    {
        return signIn(root);
    }
    else if (requestType == "sign_out")
    {
        return signOut();
    }
    else if (requestType == "get_all_users")
    {
        return allUsers();
    }
    else if (requestType == "output_message")
    {
        return outputMessage(root);
    }
    return errResponse;
}

std::string ServerProcessor::parseResponse(const ptree &root)
{
    std::string responseType = root.get<std::string>("response_type");
    if (responseType == "input_message")
    {
        return inputMessage(root);
    }
    return errResponse;
}

std::string ServerProcessor::signUp(const ptree &requestRoot)
{
    auto login = requestRoot.get<std::string>("user.login");
    auto password = requestRoot.get<std::string>("user.password");
    int userId = _db->invalidId();
    _db->getUserId(login, userId);
    if (userId != _db->invalidId())
    {
        //логин занят
        ptree responseRoot;
        responseRoot.put("response_type", "sign_up");
        responseRoot.put("status", "login_exists");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    userId = _db->insertUser(login, password);
    if (userId == _db->invalidId())
    {
        return errResponse;
    }

    if (_sessionMgr->isUserOnline(userId))
    {
        ptree responseRoot;
        responseRoot.put("response_type", "sign_up");
        responseRoot.put("status", "already_signed");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    _currentUser = userId;
    _sessionMgr->addSession(userId, _currentSession);
    ptree responseRoot;
    responseRoot.put("response_type", "sign_up");
    responseRoot.put("status", "ok");
    responseRoot.put("user.id", userId);
    responseRoot.put("user.login", login);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    return responseStream.str() + "\n";
}

std::string ServerProcessor::signIn(const ptree &requestRoot)
{
    auto login = requestRoot.get<std::string>("user.login");
    auto password = requestRoot.get<std::string>("user.password");
    int userId = _db->invalidId();

    _db->getUserId(login, userId);
    if (userId == _db->invalidId())
    {
        ptree responseRoot;
        responseRoot.put("response_type", "sign_in");
        responseRoot.put("status", "login_not_exists");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    std::string realPassword;
    if (!_db->getUserPassword(userId, realPassword))
    {
        return errResponse;
    }
    if (password != realPassword)
    {
        ptree responseRoot;
        responseRoot.put("response_type", "sign_in");
        responseRoot.put("status", "password_incorrect");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    if (_sessionMgr->isUserOnline(userId))
    {
        ptree responseRoot;
        responseRoot.put("response_type", "sign_in");
        responseRoot.put("status", "already_signed");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    _currentUser = userId;
    _sessionMgr->addSession(userId, _currentSession);
    ptree responseRoot;
    responseRoot.put("response_type", "sign_in");
    responseRoot.put("status", "ok");
    responseRoot.put("user.id", userId);
    responseRoot.put("user.login", login);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    return responseStream.str() + "\n";
}

std::string ServerProcessor::signOut()
{
    _sessionMgr->removeSession(_currentUser);
    return std::string();
}

std::string ServerProcessor::allUsers()
{
    std::vector<std::tuple<std::string, std::string> > usersData;
    if (!_db->getAllUsersData(usersData))
    {
        return errResponse;
    }
    if (!usersData.size())
    {
        ptree responseRoot;
        responseRoot.put("response_type", "get_all_users");
        responseRoot.put("status", "empty");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    ptree responseRoot;
    responseRoot.put("response_type", "get_all_users");
    responseRoot.put("status", "ok");
    ptree children;
    for (const auto &data : usersData)
    {
        ptree child;
        child.put("id", std::get<0>(data));
        child.put("login", std::get<1>(data));
        children.push_back(std::make_pair("", child));
    }
    responseRoot.add_child("users", children);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    return responseStream.str() + "\n";
}

std::string ServerProcessor::outputMessage(const ptree &root)
{
    auto id_sender = root.get<int>("sender");
    auto id_recipient = root.get<int>("recipient");
    auto text = root.get<std::string>("text");

    //отправим входящее сообщение адресату
    ptree requestRoot;
    requestRoot.put("request_type", "input_message");
    requestRoot.put("sender.id", id_sender);
    requestRoot.put("sender.login", "sender");
    requestRoot.put("text", text);
    std::stringstream stream;
    boost::property_tree::write_json(stream, requestRoot);
    _sessionMgr->sendToUser(id_recipient, stream.str() + "\n");
    return std::string();
}

std::string ServerProcessor::inputMessage(const ptree &root)
{
    auto status = root.get<std::string>("status");
    auto id_sender = root.get<int>("sender");
//    auto id_recipient = root.get<int>("recipient");
    auto text = root.get<std::string>("text");

    //отправим ответ отправителю на его исходящее сообщение
    ptree responseRoot;
    responseRoot.put("response_type", "output_message");
    responseRoot.put("status", status);
    responseRoot.put("text", text);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    _sessionMgr->sendToUser(id_sender, responseStream.str() + "\n");
    return std::string();
}
