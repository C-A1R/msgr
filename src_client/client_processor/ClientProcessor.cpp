#include "ClientProcessor.h"
#include "client/ClientThread.h"
#include "UserInfo.h"
#include "MessageInfo.h"
#include "Notification.h"

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
    emit signal_sendRequest(Request("sign_up")
                            .writeSignUser(login.toStdString(), password.toStdString())
                            .toJson());
}

void ClientProcessor::signIn_request(const QString &login, const QString &password)
{
    if (login.isEmpty() || password.isEmpty())
    {
        return;
    }
    emit signal_sendRequest(Request("sign_in")
                            .writeSignUser(login.toStdString(), password.toStdString())
                            .toJson());
}

void ClientProcessor::signOut_request()
{  
    emit signal_sendRequest(Request("sign_out")
                            .writeValue("user_id", currentUser()->id)
                            .toJson());
}

void ClientProcessor::getUsers_request()
{
    emit signal_sendRequest(Request("get_all_users").toJson());
}

void ClientProcessor::outputMessage_request(int contactId, const std::string &msg)
{
    if (msg.empty())
    {
        return;
    }

    emit signal_sendRequest(Request("output_message")
                            .writeMessage(-1, _currentUser->id, contactId, msg)
                            .toJson());
}

void ClientProcessor::getMessages_request(int contactId, int lastMessageId)
{
    emit signal_sendRequest(Request("get_messages")
                            .writeValue("user_1", _currentUser->id)
                            .writeValue("user_2", contactId)
                            .writeValue("last_message", lastMessageId)
                            .toJson());
}

void ClientProcessor::inputMessage_response(const std::shared_ptr<MessageInfo> &message)
{
    emit signal_sendResponse(Response("input_message")
                             .writeStatusOk()
                             .writeMessage(message->id, message->senderId, _currentUser->id, message->text)
                             .toJson());
}

void ClientProcessor::slot_parseRecieved(const std::string &msg)
{
    std::cout << "msg " << msg;
    if (msg.empty()
            || msg == "#pong\n"     //соединение установлено
            || msg == "#large\n")   //сервер хочет передать длинное сообщение по частям
    {
        return;
    }

    auto notificationType = Notification::readNotificationType(msg);
    if (notificationType == NotificationType::type_request)
    {
        parseRequest(Request::fromJson(msg));
    }
    else if (notificationType == NotificationType::type_response)
    {
        parseResponse(Response::fromJson(msg));
    }
}

void ClientProcessor::parseRequest(const Request &request)
{
    const auto requestType = request.type();
    if (requestType == "input_message")
    {
        emit signal_inputMessageRequest(request.readMessage());
    }
    if (requestType == "new_user_registered")
    {
        emit signal_newUserRegistered(request.readUser());
    }
}

void ClientProcessor::parseResponse(const Response &response)
{
    const auto responseType = response.type();
    if (responseType == "sign_up")
    {
        auto status = response.status();
        if (status == Response::ok())
        {
            _currentUser = response.readUser();
        }
        emit signal_signUpResponse(status);
    }
    if (responseType == "sign_in")
    {
        auto status = response.status();
        if (status == Response::ok())
        {
            _currentUser = response.readUser();
        }
        emit signal_signInResponse(status);
    }
    if (responseType == "output_message")
    {
        auto status = response.status();
        if (status == Response::ok())
        {
            emit signal_outputMessageResponse(response.readMessage());
        }
    }
    if (responseType == "get_all_users")
    {
        auto status = response.status();
        if (status == Response::ok())
        {
            emit signal_getUsersResponse(response.readUsers());
        }
    }
    if (responseType == "get_messages")
    {
        auto status = response.status();
        if (status == Response::ok())
        {
            auto messages = response.readMessages();
            std::sort(messages.begin(), messages.end(), [](const std::shared_ptr<MessageInfo> &m1, const std::shared_ptr<MessageInfo> &m2) -> bool
            {
                return m1->id < m2->id;
            });
            emit signal_getMessagesResponse(messages);
        }
    }
}
