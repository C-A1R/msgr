#include "MsgProcessor.h"

#include "client/ClientThread.h"

//#include <boost/json.hpp>

#include <QtDebug>

MsgProcessor::MsgProcessor()
{
    _clientThread = std::make_unique<ClientThread>();
    connect(this, &MsgProcessor::signal_stopClient, _clientThread.get(), &ClientThread::slot_stopClient);
    connect(this, &MsgProcessor::signal_sendToClientThread, _clientThread.get(), &ClientThread::signal_sendToClient);
    connect(_clientThread.get(), &ClientThread::signal_getFromThread, this, &MsgProcessor::slot_getMsg);

    connect(this, &MsgProcessor::signal_sendRequest, _clientThread.get(), &ClientThread::signal_sendToClient);
}

MsgProcessor::~MsgProcessor()
{
    emit signal_stopClient();
    _clientThread->wait(100);
}

void MsgProcessor::start()
{
    _clientThread->start();
}

void MsgProcessor::sendMsg(const QString &msg)
{
    //generate REST
    if (msg.isEmpty())
    {
        return;
    }
    emit signal_sendToClientThread(msg);
}

void MsgProcessor::signUp_request(const QString &login, const QString &password)
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

void MsgProcessor::slot_getMsg(const QString &msg)
{
    //parsing REST
    if (msg.isEmpty())
    {
        return;
    }
    emit signal_sendToGui(msg);
}
