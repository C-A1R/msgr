#include "ServerProcessor.h"
#include "Session.h"
#include "SessionManager.h"
#include "database/SqliteDatabase.h"
#include "UserInfo.h"
#include "MessageInfo.h"
#include "Notification.h"

#include <boost/property_tree/json_parser.hpp>

#include <iostream>

ServerProcessor::ServerProcessor(const std::shared_ptr<IDatabase> &db,
                                 const std::shared_ptr<SessionManager> &sessionMgr,
                                 const std::shared_ptr<Session> &currentSession)
    : _db{db}, _sessionMgr{sessionMgr}, _currentSession{currentSession}
{
}

std::string ServerProcessor::parseClientMessage(const std::string &msg) const
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

    auto notificationType = Notification::readNotificationType(msg);
    if (notificationType == NotificationType::type_request)
    {
        return parseRequest(Request::fromJson(msg));
    }
    else if (notificationType == NotificationType::type_response)
    {
        return parseResponse(Response::fromJson(msg));
    }

    return std::string();
}

std::string ServerProcessor::parseRequest(const Request &request) const
{
    const auto requestType = request.type();
    if (requestType == "sign_up")
    {
        return signUp(request);
    }
    else if (requestType == "sign_in")
    {
        return signIn(request);
    }
    else if (requestType == "sign_out")
    {
        return signOut(request);
    }
    else if (requestType == "get_all_users")
    {
        return allUsers();
    }
    else if (requestType == "output_message")
    {
        return outputMessage(request);
    }
    else if (requestType == "get_messages")
    {
        return getMessages(request);
    }
    return Response::errResponse();
}

std::string ServerProcessor::parseResponse(const Response &response) const
{
    const auto responseType = response.type();
    if (responseType == "input_message")
    {
        return inputMessage(response);
    }
    return Response::errResponse();
}

std::string ServerProcessor::signUp(const Request &request) const
{
    std::string login, password;
    std::tie(login, password) = request.readSignUser();
    int userId = _db->invalidId();
    _db->getUserId(login, userId);
    if (userId != _db->invalidId())
    {
        //логин занят
        return Response("sign_up")
                .writeStatus("login_exists")
                .toJson();
    }

    userId = _db->insertUser(std::make_pair(login, password));
    if (userId == _db->invalidId())
    {
        return Response::errResponse();
    }

    //сообщим всем о новом пользователе
    _sessionMgr->sendToAll(Request("new_user_registered")
                           .writeUser(userId, login, "")
                           .toJson());
    _sessionMgr->addSession(userId, _currentSession);

    return Response("sign_up")
            .writeStatusOk()
            .writeUser(userId, login, "")
            .toJson();
}

std::string ServerProcessor::signIn(const Request &request) const
{
    std::string login, password;
    std::tie(login, password) = request.readSignUser();
    int userId = _db->invalidId();

    _db->getUserId(login, userId);
    if (userId == _db->invalidId())
    {
        return Response("sign_in")
                .writeStatus("login_not_exists")
                .toJson();
    }

    std::string realPassword;
    if (!_db->getUserPassword(userId, realPassword))
    {
        return Response::errResponse();
    }
    if (password != realPassword)
    {
        return Response("sign_in")
                .writeStatus("password_incorrect")
                .toJson();
    }

    if (_sessionMgr->isUserOnline(userId))
    {
        return Response("sign_in")
                .writeStatus("already_signed")
                .toJson();
    }

    std::string username;
    _db->getUsername(userId, username);

    _sessionMgr->addSession(userId, _currentSession);
    return Response("sign_in")
            .writeStatusOk()
            .writeUser(userId, login, username)
            .toJson();
}

std::string ServerProcessor::signOut(const Request &request) const
{
    _sessionMgr->removeSession(request.readValue<int>("user_id"));
    return std::string();
}

std::string ServerProcessor::allUsers() const
{
    std::vector<UserInfo> users;
    if (!_db->getAllUsers(users))
    {
        return Response::errResponse();
    }
    if (!users.size())
    {
        return Response("get_all_users")
                .writeStatus("empty")
                .toJson();
    }

    return Response("get_all_users")
            .writeStatusOk()
            .writeUsers(users)
            .toJson();
}

std::string ServerProcessor::outputMessage(const Request &request) const
{
    auto message = request.readMessage();

    ///@todo экранировать кавычки и тд в тексте
    auto msgId = _db->insertMessage(message->senderId, message->recipientId, message->text);
    if (msgId == _db->invalidId())
    {
        return Response::errResponse();
    }
    message->id = msgId;

    if (_sessionMgr->isUserOnline(message->recipientId))
    {
        //отправим входящее сообщение адресату
        _sessionMgr->sendToUser(message->recipientId, Request("input_message")
                                                       .writeMessage(message)
                                                       .toJson());
        return std::string();
    }

    return Response("output_message")
            .writeStatusOk()
            .writeMessage(message)
            .toJson();
}

std::string ServerProcessor::inputMessage(const Response &response) const
{
    const auto status = response.status();
    const auto msg = response.readMessage();

    //отправим ответ отправителю на его исходящее сообщение
    _sessionMgr->sendToUser(msg->senderId, Response("output_message")
                                            .writeStatus(status)
                                            .writeMessage(msg)
                                            .toJson());
    return std::string();
}

std::string ServerProcessor::getMessages(const Request &request) const
{
    auto user_1 = request.readValue<int>("user_1");
    auto user_2 = request.readValue<int>("user_2");
    auto lastId = request.readValue<int>("last_message");

    std::vector<MessageInfo> messages;
    if (!_db->getMessages(user_1, user_2, lastId, messages))
    {
        return Response::errResponse();
    }
    if (!messages.size())
    {
        return Response("get_messages")
                .writeStatus("empty")
                .toJson();
    }

    return Response("get_messages")
            .writeStatusOk()
            .writeMessages(messages)
            .toJson();
}
