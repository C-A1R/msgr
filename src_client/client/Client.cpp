#include "Client.h"

#include <iostream>

Client::Client(boost::asio::io_context &io_context)
    : _socket{io_context}, _resolver{io_context}
{
}

void Client::start(const std::string &host, const std::string &service)
{
    tcp::resolver::query query{host, service};
    _resolver.async_resolve(query, [&](const boost::system::error_code &ec, tcp::resolver::iterator it)
    {
        resolveHandler(ec, it);
    });
}

void Client::resolveHandler(const boost::system::error_code &ec, tcp::resolver::iterator it)
{
    if (ec || it == tcp::resolver::iterator{})
    {
        return;
    }
//    std::cout << "# / endpoint " << it->endpoint().address() << ":" << it->endpoint().port() << std::endl;

    _socket.async_connect(*it, [&](const boost::system::error_code &ec)
    {
        connectHandler(ec);
    });
}

void Client::connectHandler(const boost::system::error_code &ec)
{
    if (ec)
    {
        return;
    }
    writeHandler("ping\n");
}

void Client::readHandler(const boost::system::error_code &ec, std::size_t bytes)
{
    if (ec || !bytes)
    {
        return;
    }

    _socket.async_read_some(boost::asio::buffer(_buffer), [&](const boost::system::error_code &ec, std::size_t bytes)
    {
        std::cout << "# READ " << std::string(_buffer, bytes);
        emit signal_getMsgFromServer(QString(_buffer));
        readHandler(ec, bytes);
    });
}

void Client::slot_sendMsgToServer(QString msg)
{
    std::cout << "# slot_sendMsgToServer " << msg.toStdString() << std::endl;
    writeHandler(msg.toStdString() + "\n");
}

void Client::writeHandler(const std::string &msg)
{
    if (msg.empty())
    {
        return;
    }
    //    std::cout << "# WRITE " << msg;
    _socket.async_write_some(boost::asio::buffer(msg), [&](const boost::system::error_code &ec, std::size_t bytes)
    {
        if (!ec)
            readHandler(ec, bytes);
    });
}
