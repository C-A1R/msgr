#include "Client.h"

#include <iostream>

Client::Client(boost::asio::io_context &io_context)
    : _socket{io_context}, _resolver{io_context}
{
}

void Client::start(const std::string &host, const std::string &service)
{
    std::cout << "# / Client::start " << host << " " << service << std::endl;
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
        std::cout << "# / ec " << ec.message() << std::endl;
        return;
    }
    std::cout << "# / endpoint " << it->endpoint().address() << ":" << it->endpoint().port() << std::endl;

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
    std::cout << "# / ping " << std::endl;
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
        emit signal_getFromServer(std::string(_buffer, bytes));
        readHandler(ec, bytes);
    });
}

void Client::slot_sendToServer(const std::string &request)
{    
    writeHandler(request);
}

void Client::writeHandler(const std::string &msg)
{
    if (msg.empty())
    {
        return;
    }
    _socket.async_write_some(boost::asio::buffer(msg), [&](const boost::system::error_code &ec, std::size_t bytes)
    {
        if (!ec)
        {
            readHandler(ec, bytes);
        }
    });
}
