#include "ClientProcessor.h"

#include "client/ClientThread.h"

//#include <boost/json.hpp>

#include <QtDebug>

ClientProcessor::ClientProcessor()
{
    _clientThread = std::make_unique<ClientThread>();
    connect(this, &ClientProcessor::signal_stopClient, _clientThread.get(), &ClientThread::slot_stopClient);
    connect(this, &ClientProcessor::signal_sendToClientThread, _clientThread.get(), &ClientThread::signal_sendToClient);
    connect(_clientThread.get(), &ClientThread::signal_getFromThread, this, &ClientProcessor::slot_getMsg);

    connect(this, &ClientProcessor::signal_sendRequest, _clientThread.get(), &ClientThread::signal_sendToClient);
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

void ClientProcessor::sendMsg(const QString &msg)
{
    //generate REST
    if (msg.isEmpty())
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
    auto request = QStringLiteral("{"
                                      "\"user:\""
                                      "{"
                                          "\"login\": \"%1\""
                                          "\"password\": \"%2\""
                                      "}"
                                  "}");
    emit signal_sendRequest(request.arg(login, password));
}

void ClientProcessor::slot_getMsg(const QString &msg)
{
    //parsing REST
    if (msg.isEmpty())
    {
        return;
    }
    emit signal_sendToGui(msg);
}
