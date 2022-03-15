#include "ClientThread.h"

ClientThread::ClientThread()
{
    _client = std::make_unique<Client>(_io_context);
    connect(this, &ClientThread::signal_sendMsgToThread, _client.get(), &Client::slot_sendMsgToServer);
    connect(_client.get(), &Client::signal_getMsgFromServer, this, &ClientThread::signal_getMsgFromThread);
}

ClientThread::~ClientThread()
{
    _io_context.stop();
    exit();
}

void ClientThread::run()
{
    _client->start("localhost", "9000");
    _io_context.run();
}

void ClientThread::slot_stopClient()
{
    _io_context.stop();
    exit();
}
