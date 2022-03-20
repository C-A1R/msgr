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
        do_resolve(ec, it);
    });
}

void Client::do_resolve(const boost::system::error_code &ec, tcp::resolver::iterator it)
{
    if (ec || it == tcp::resolver::iterator{})
    {
        return;
    }
//    std::cout << "# / endpoint " << it->endpoint().address() << ":" << it->endpoint().port() << std::endl;

    _socket.async_connect(*it, [&](const boost::system::error_code &ec)
    {
        do_connect(ec);
    });
}

void Client::do_connect(const boost::system::error_code &ec)
{
    if (ec)
    {
        return;
    }
    do_write("#ping\n");
}

void Client::do_read(const boost::system::error_code &ec, std::size_t bytes)
{
    if (ec || !bytes)
    {
        return;
    }

    _socket.async_read_some(boost::asio::buffer(_buffer), [&](const boost::system::error_code &ec, std::size_t bytes)
    {
        auto str = std::string(_buffer, bytes);
        emit signal_recieved(str);
        if (str == "#large\n")
        {
            do_read_large(ec, bytes);
        }
        else
        {
            do_read(ec, bytes);
        }
    });
}

void Client::do_read_large(const boost::system::error_code &ec, std::size_t bytes)
{
    if (ec || !bytes)
    {
        return;
    }

    _socket.write_some(boost::asio::buffer(std::string("#ready\n")));
    do
    {
        auto byts = _socket.read_some(boost::asio::buffer(_buffer));
        _bufferLarge += std::string(_buffer, byts);
    }
    while (_bufferLarge.at(_bufferLarge.length() - 1) != '\n');

    emit signal_recieved(_bufferLarge);
    _bufferLarge.clear();
}

void Client::send(const std::string &msg)
{    
    do_write(msg);
}

void Client::do_write(const std::string &msg)
{
    if (msg.empty())
    {
        return;
    }
    _socket.async_write_some(boost::asio::buffer(msg), [&](const boost::system::error_code &ec, std::size_t bytes)
    {
        if (!ec)
        {
            do_read(ec, bytes);
        }
    });
}
