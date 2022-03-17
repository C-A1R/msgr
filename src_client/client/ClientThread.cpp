#include "ClientThread.h"

#include "iostream"

ClientThread::ClientThread()
{
    _client = std::make_unique<Client>(_io_context);
    connect(this, &ClientThread::signal_sendToClient, _client.get(), &Client::slot_sendToServer);
    connect(_client.get(), &Client::signal_responseRecieved, this, &ClientThread::signal_responseRecieved);
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
