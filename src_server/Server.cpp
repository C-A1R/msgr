#include "Server.h"

#include "Session.h"
#include "server_processor/ServerProcessor.h"

#include <filesystem>
#include <iostream>

Server::Server(boost::asio::io_context& io_context, int port)
    : _acceptor{io_context, tcp::endpoint(tcp::v4(), port)}
{
    const char *dbName = "db.sqlite";
    _db = std::make_shared<Database>(dbName);
    std::filesystem::path dbPath = std::filesystem::current_path() / dbName;
    bool baseCreated = std::filesystem::exists(dbPath);

    if (!_db->open())
    {
        return;
    }
    if (!baseCreated && !_db->create())
    {
        return;
    }
    do_accept();
}

void Server::do_accept() 
{
    _acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            std::make_shared<Session>(std::move(socket), std::make_unique<ServerProcessor>(_db))->start();
        }
        do_accept();
    });
}
