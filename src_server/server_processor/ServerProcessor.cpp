#include "ServerProcessor.h"
#include "Session.h"
#include "SessionManager.h"
#include "database/SqliteDatabase.h"
#include "UserInfo.h"
#include "MessageInfo.h"

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
    std::cout << "msg " << msg;
    if (msg == "#ping\n")
    {
        return "#pong\n";
    }
    if (msg == "#large\n")
    {
        return msg;
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
        return signOut(root);
    }
    else if (requestType == "get_all_users")
    {
        return allUsers();
    }
    else if (requestType == "output_message")
    {
        return outputMessage(root);
    }
    else if (requestType == "get_messages")
    {
        return getMessages(root);
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

    userId = _db->insertUser(std::make_pair(login, password));
    if (userId == _db->invalidId())
    {
        return errResponse;
    }

    {
        //сообщим всем о новом пользователе
        ptree root;
        root.put("request_type", "new_user_registered");
        root.put("user.id", userId);
        root.put("user.login", login);
        root.put("user.name", "");
        std::stringstream stream;
        boost::property_tree::write_json(stream, root);
        _sessionMgr->sendToAll(stream.str() + "\n");
    }

    _sessionMgr->addSession(userId, _currentSession);
    ptree responseRoot;
    responseRoot.put("response_type", "sign_up");
    responseRoot.put("status", "ok");
    responseRoot.put("user.id", userId);
    responseRoot.put("user.login", login);
    responseRoot.put("user.name", "");
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

    std::string username;
    _db->getUsername(userId, username);

    _sessionMgr->addSession(userId, _currentSession);
    ptree responseRoot;
    responseRoot.put("response_type", "sign_in");
    responseRoot.put("status", "ok");
    responseRoot.put("user.id", userId);
    responseRoot.put("user.login", login);
    responseRoot.put("user.name", username);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    return responseStream.str() + "\n";
}

std::string ServerProcessor::signOut(const ptree &root)
{
    _sessionMgr->removeSession(root.get<int>("user_id"));
    return std::string();
}

std::string ServerProcessor::allUsers()
{
    std::vector<UserInfo> users;
    if (!_db->getAllUsers(users))
    {
        return errResponse;
    }
    if (!users.size())
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
    for (const auto &user : users)
    {
        ptree child;
        child.put("id", user.id);
        child.put("login", user.login);
        child.put("name", user.name);
        children.push_back(std::make_pair("", child));
    }
    responseRoot.add_child("users", children);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    return responseStream.str() + "\n";
}

std::string ServerProcessor::outputMessage(const ptree &root)
{
    auto id_sender = root.get<int>("message.sender");
    auto id_recipient = root.get<int>("message.recipient");
    auto text = root.get<std::string>("message.text");

    ///@todo экранировать кавычки и тд в тексте
    auto msgId = _db->insertMessage(id_sender, id_recipient, text);
    if (msgId == _db->invalidId())
    {
        return errResponse;
    }

    if (_sessionMgr->isUserOnline(id_recipient))
    {
        //отправим входящее сообщение адресату
        ptree requestRoot;
        requestRoot.put("request_type", "input_message");
        requestRoot.put("message.id", msgId);
        requestRoot.put("message.sender", id_sender);
        requestRoot.put("message.recipient", id_recipient);
        requestRoot.put("message.text", text);
        std::stringstream stream;
        boost::property_tree::write_json(stream, requestRoot);
        _sessionMgr->sendToUser(id_recipient, stream.str() + "\n");
        return std::string();
    }

    ptree responseRoot;
    responseRoot.put("response_type", "output_message");
    responseRoot.put("status", "ok");
    responseRoot.put("message.id", msgId);
    responseRoot.put("message.sender", id_sender);
    responseRoot.put("message.recipient", id_recipient);
    responseRoot.put("message.text", text);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    return responseStream.str() + "\n";
}

std::string ServerProcessor::inputMessage(const ptree &root)
{
    auto status = root.get<std::string>("status");
    auto id_msg = root.get<int>("message.id");
    auto id_sender = root.get<int>("message.sender");
    auto id_recipient = root.get<int>("message.recipient");
    auto text = root.get<std::string>("message.text");

    //отправим ответ отправителю на его исходящее сообщение
    ptree responseRoot;
    responseRoot.put("response_type", "output_message");
    responseRoot.put("status", status);
    responseRoot.put("message.id", id_msg);
    responseRoot.put("message.sender", id_sender);
    responseRoot.put("message.recipient", id_recipient);
    responseRoot.put("message.text", text);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    _sessionMgr->sendToUser(id_sender, responseStream.str() + "\n");
    return std::string();
}

std::string ServerProcessor::getMessages(const boost::property_tree::ptree &requestRoot)
{
    auto user_1 = requestRoot.get<int>("user_1");
    auto user_2 = requestRoot.get<int>("user_2");
    auto lastId = requestRoot.get<int>("last_message");

    std::vector<MessageInfo> messages;
    if (!_db->getMessages(user_1, user_2, lastId, messages))
    {
        return errResponse;
    }
    if (!messages.size())
    {
        ptree responseRoot;
        responseRoot.put("response_type", "get_messages");
        responseRoot.put("status", "empty");
        std::stringstream responseStream;
        boost::property_tree::write_json(responseStream, responseRoot);
        return responseStream.str() + "\n";
    }

    ptree responseRoot;
    responseRoot.put("response_type", "get_messages");
    responseRoot.put("status", "ok");
    ptree children;
    for (const auto &msg : messages)
    {
        ptree child;
        child.put("id", msg.id);
        child.put("sender", msg.senderId);
        child.put("recipient", msg.recipientId);
        child.put("text", msg.text);
        children.push_back(std::make_pair("", child));
    }
    responseRoot.add_child("messages", children);
    std::stringstream responseStream;
    boost::property_tree::write_json(responseStream, responseRoot);
    return responseStream.str() + "\n";
}
