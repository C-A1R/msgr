#include "ClientProcessor.h"

#include "client/ClientThread.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <iostream>

ClientProcessor::ClientProcessor()
{
    _clientThread = std::make_unique<ClientThread>();
    connect(this, &ClientProcessor::signal_stopClient, _clientThread.get(), &ClientThread::slot_stopClient);
    connect(this, &ClientProcessor::signal_sendToClientThread, _clientThread.get(), &ClientThread::signal_sendToClient);

    connect(this, &ClientProcessor::signal_sendRequest, _clientThread.get(), &ClientThread::signal_sendToClient);
    connect(_clientThread.get(), &ClientThread::signal_getFromThread, this, &ClientProcessor::slot_getResponse);
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

void ClientProcessor::sendMsg(const std::string &msg)
{
    if (msg.empty())
    {
        return;
    }
    emit signal_sendToClientThread(msg);
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

void ClientProcessor::slot_getResponse(const std::string &response)
{
    std::cout << "# response " << response;
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
        emit signal_signUpResponse(root.get<std::string>("status"));
    }

//    emit signal_sendToGui(response);
}
