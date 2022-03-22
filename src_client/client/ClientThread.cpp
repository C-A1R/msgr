#include "ClientThread.h"


ClientThread::ClientThread()
{
    _client = std::make_unique<Client>(_io_context);
    connect(_client.get(), &Client::signal_recieved, this, &ClientThread::signal_recieved);
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

void ClientThread::slot_send(const std::string &msg)
{
    _client->send(msg);
}
