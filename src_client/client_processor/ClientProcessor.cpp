#include "ClientProcessor.h"

#include "client/ClientThread.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

ClientProcessor::ClientProcessor()
{
    _clientThread = std::make_unique<ClientThread>();
    connect(this, &ClientProcessor::signal_stopClient, _clientThread.get(), &ClientThread::slot_stopClient);
    ///отправка запроса
    connect(this, &ClientProcessor::signal_sendRequest, _clientThread.get(), &ClientThread::signal_sendToClient);
    ///полуение ответа
    connect(_clientThread.get(), &ClientThread::signal_responseRecieved, this, &ClientProcessor::slot_parseResponse);
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

    boost::property_tree::ptree root;
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

    boost::property_tree::ptree root;
    root.put("request_type", "sign_in");
    root.put("user.login", login.toStdString());
    root.put("user.password", password.toStdString());
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

    boost::property_tree::ptree root;
    root.put("request_type", "output_message");
    root.put("sender", currentUser.id);
    root.put("recipient", 3);
    root.put("text", msg);
    std::stringstream stream;
    boost::property_tree::write_json(stream, root);
    emit signal_sendRequest(stream.str() + "\n");
}

void ClientProcessor::slot_parseResponse(const std::string &response)
{
    std::cout << response;
    if (response.empty() || response == "pong\n")
    {
        return;
    }

    std::stringstream stream(response);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(stream, root);

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
}
