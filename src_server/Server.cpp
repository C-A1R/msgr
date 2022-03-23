#include "Server.h"

#include "session/Session.h"
#include "session/SessionManager.h"
#include "server_processor/ServerProcessor.h"
#include "database/SqliteDatabase.h"

#include <filesystem>
#include <iostream>
#include <exception>

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context, int port)
    : _acceptor{io_context, tcp::endpoint(tcp::v4(), port)}
{
    const char *dbName = "db.sqlite";
    _db = std::make_shared<SqliteDatabase>(dbName);
    std::filesystem::path dbPath = std::filesystem::current_path() / dbName;
    bool baseCreated = std::filesystem::exists(dbPath);

    if (!_db->open())
    {
        throw std::runtime_error("database is not opened");
    }
    if (!baseCreated && !_db->create())
    {
        throw std::runtime_error("database tables are not created");
    }
    _sessionManager = std::make_shared<SessionManager>();
    do_accept();
}

void Server::do_accept() 
{
    _acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            auto session = std::make_shared<Session>(std::move(socket));
            session->setProcessor(std::make_unique<ServerProcessor>(_db, _sessionManager, session));
            session->start();
        }
        do_accept();
    });
}
