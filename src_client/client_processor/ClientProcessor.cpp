#include "ClientProcessor.h"
#include "client/ClientThread.h"

#include <boost/property_tree/json_parser.hpp>

#include <iostream>

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

void ClientProcessor::outputMessage_request(const std::string &msg)
{
    if (msg.empty())
    {
        return;
    }

    ptree root;
    root.put("request_type", "output_message");
    root.put("sender", currentUser.id);
    root.put("recipient", 3);
    root.put("text", msg);
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    emit signal_sendRequest(stream.str() + "\n");
}

void ClientProcessor::inputMessage_response(const std::string &text)
{
    ptree root;
    root.put("response_type", "input_message");
    root.put("status", "ok");
    root.put("sender", 1);
    root.put("recipient", currentUser.id);
    root.put("text", text);
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
        emit signal_inputMessageRequest(root.get<std::string>("sender.login"), root.get<std::string>("text"));
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
            currentUser.id = root.get<int>("user.id");
            currentUser.login = root.get<std::string>("user.login");
        }
        emit signal_signUpResponse(status);
    }
    if (responseType == "sign_in")
    {
        auto status = root.get<std::string>("status");
        if (status == "ok")
        {
            currentUser.id = root.get<int>("user.id");
            currentUser.login = root.get<std::string>("user.login");
        }
        emit signal_signInResponse(status);
    }
    if (responseType == "output_message")
    {
        auto status = root.get<std::string>("status");
        if (status == "ok")
        {
            emit signal_outputMessageResponse(root.get<std::string>("text"));
        }
    }
    if (responseType == "get_all_users")
    {
        auto status = root.get<std::string>("status");
        if (status == "ok")
        {
            std::vector<UserInfo> users;
            auto usersTree = root.get_child("users");
            for (auto u : usersTree)
            {
                users.emplace_back(std::stoi(u.second.get<std::string>("id")), u.second.get<std::string>("login"));
            }
            emit signal_getUsersResponse(users);
        }
    }
}
