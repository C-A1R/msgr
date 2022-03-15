#include "server.h"

#include "session.h"

Server::Server(boost::asio::io_context& io_context, int port)
    : _acceptor{io_context, tcp::endpoint(tcp::v4(), port)}
{
    do_accept();
}

void Server::do_accept() 
{
    _acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            std::make_shared<Session>(std::move(socket))->start();
        }
        do_accept();
    });
}