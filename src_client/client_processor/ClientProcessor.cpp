#include "ClientProcessor.h"
#include "client/ClientThread.h"
#include "../../src_shared/UserInfo.h"
#include "../../src_shared/MessageInfo.h"

#include <boost/property_tree/json_parser.hpp>

#include <iostream>
#include <algorithm>

ClientProcessor::ClientProcessor()
{
    _clientThread = std::make_unique<ClientThread>();
    connect(this, &ClientProcessor::signal_stopClient, _clientThread.get(), &ClientThread::slot_stopClient);
    ///отправка запроса на сервер
    connect(this, &ClientProcessor::signal_sendRequest, _clientThread.get(), &ClientThread::slot_send);
    ///получение ответа от сервера
    connect(_clientThread.get(), &ClientThread::signal_recieved, this, &ClientProcessor::slot_parseRecieved);
    ///отправка ответа на сервер
    connect(this, &ClientProcessor::signal_sendResponse, _clientThread.get(), &ClientThread::slot_send);
}

ClientProcessor::~ClientProcessor()
{
    emit signal_stopClient();
    _clientThread->wait(100);
}

std::shared_ptr<UserInfo> ClientProcessor::currentUser() const
{
    return _currentUser;
}

void ClientProcessor::start()
{
    _clientThread->start();
}

void ClientProcessor::signUp_request(const QString &login, const QString &password)
{
    if (login.isEmpty() || password.isEmpty())
    {
        return;
    }

    ptree root;
    root.put("request_type", "sign_up");
    root.put("user.login", login.toStdString());
    root.put("user.password", password.toStdString());
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    emit signal_sendRequest(stream.str() + "\n");
}

void ClientProcessor::signIn_request(const QString &login, const QString &password)
{
    if (login.isEmpty() || password.isEmpty())
    {
        return;
    }

    ptree root;
    root.put("request_type", "sign_in");
    root.put("user.login", login.toStdString());
    root.put("user.password", password.toStdString());
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    emit signal_sendRequest(stream.str() + "\n");
}

void ClientProcessor::signOut_request()
{
    ptree root;
    root.put("request_type", "sign_out");
    root.put("user_id", currentUser()->id);
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    emit signal_sendRequest(stream.str() + "\n");
}

void ClientProcessor::getUsers_request()
{
    ptree root;
    root.put("request_type", "get_all_users");
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    emit signal_sendRequest(stream.str() + "\n");
}

void ClientProcessor::outputMessage_request(int contactId, const std::string &msg)
{
    if (msg.empty())
    {
        return;
    }

    ptree root;
    root.put("request_type", "output_message");
    root.put("message.sender", _currentUser->id);
    root.put("message.recipient", contactId);
    root.put("message.text", msg);
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    emit signal_sendRequest(stream.str() + "\n");
}

void ClientProcessor::getMessages_request(int contactId, int lastMessageId)
{
    ptree root;
    root.put("request_type", "get_messages");
    root.put("user_1", _currentUser->id);
    root.put("user_2", contactId);
    root.put("last_message", lastMessageId);
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    emit signal_sendRequest(stream.str() + "\n");
}

void ClientProcessor::inputMessage_response(const std::shared_ptr<MessageInfo> &message)
{
    ptree root;
    root.put("response_type", "input_message");
    root.put("status", "ok");
    root.put("message.id", message->id);
    root.put("message.sender", message->senderId);
    root.put("message.recipient", _currentUser->id);
    root.put("message.text", message->text);
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    emit signal_sendResponse(stream.str() + "\n");
}

void ClientProcessor::slot_parseRecieved(const std::string &msg)
{
    std::cout << msg;
    if (msg.empty() || msg == "pong\n")
    {
        return;
    }

    std::stringstream stream(msg);
    ptree root;
    boost::property_tree::read_json(stream, root);

    if (root.count("response_type") > 0)
    {
        parseResponse(root);
    }
    else if (root.count("request_type") > 0)
    {
        parseRequest(root);
    }
}

void ClientProcessor::parseRequest(const ptree &root)
{
    std::string requestType = root.get<std::string>("request_type");
    if (requestType == "input_message")
    {
        auto message = std::make_shared<MessageInfo>();
        message->id = root.get<int>("message.id");
        message->senderId = root.get<int>("message.sender");
        message->recipientId = root.get<int>("message.recipient");
        message->text = root.get<std::string>("message.text");
        emit signal_inputMessageRequest(message);
    }
    if (requestType == "new_user_registered")
    {
        auto user = std::make_shared<UserInfo>();
        user->id = root.get<int>("user.id");
        user->login = root.get<std::string>("user.login");
        user->name = root.get<std::string>("user.name");
        emit signal_newUserRegistered(user);
    }
}

void ClientProcessor::parseResponse(const ptree &root)
{
    std::string responseType = root.get<std::string>("response_type");
    if (responseType == "sign_up")
    {
        auto status = root.get<std::string>("status");
        if (status == "ok")
        {
            _currentUser = std::make_shared<UserInfo>();
            _currentUser->id = root.get<int>("user.id");
            _currentUser->login = root.get<std::string>("user.login");
            _currentUser->name = root.get<std::string>("user.name");
        }
        emit signal_signUpResponse(status);
    }
    if (responseType == "sign_in")
    {
        auto status = root.get<std::string>("status");
        if (status == "ok")
        {
            _currentUser = std::make_shared<UserInfo>();
            _currentUser->id = root.get<int>("user.id");
            _currentUser->login = root.get<std::string>("user.login");
            _currentUser->name = root.get<std::string>("user.name");
        }
        emit signal_signInResponse(status);
    }
    if (responseType == "output_message")
    {
        auto status = root.get<std::string>("status");
        if (status == "ok")
        {
            auto message = std::make_shared<MessageInfo>();
            message->id =  root.get<int>("message.id");;
            message->senderId = root.get<int>("message.sender");
            message->recipientId = root.get<int>("message.recipient");
            message->text = root.get<std::string>("message.text");
            emit signal_outputMessageResponse(message);
        }
    }
    if (responseType == "get_all_users")
    {
        auto status = root.get<std::string>("status");
        if (status == "ok")
        {
            std::vector<std::shared_ptr<UserInfo> > users;
            auto usersRoot = root.get_child("users");
            for (const auto &u : usersRoot)
            {
                auto id = u.second.get<int>("id");
                if (id == _currentUser->id)
                    continue;
                auto user = std::make_shared<UserInfo>();
                user->id = id;
                user->login = u.second.get<std::string>("login");
                user->name = u.second.get<std::string>("name");
                users.push_back(user);
            }
            emit signal_getUsersResponse(users);
        }
    }
    if (responseType == "get_messages")
    {
        auto status = root.get<std::string>("status");
        if (status == "ok")
        {
            std::vector<std::shared_ptr<MessageInfo> > messages;
            auto messagesRoot = root.get_child("messages");
            for (const auto &m : messagesRoot)
            {
                auto msg = std::make_shared<MessageInfo>();
                msg->id = m.second.get<int>("id");
                msg->senderId = m.second.get<int>("sender");
                msg->recipientId = m.second.get<int>("recipient");
                msg->text = m.second.get<std::string>("text");
                messages.push_back(msg);
            }
            std::sort(messages.begin(), messages.end(), [](const std::shared_ptr<MessageInfo> &m1, const std::shared_ptr<MessageInfo> &m2) -> bool
            {
                return m1->id < m2->id;
            });
            emit signal_getMessagesResponse(messages);
        }
    }
}
