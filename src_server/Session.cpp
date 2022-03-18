#include "Session.h"

#include <iostream>
#include <string>

Session::Session(tcp::socket socket)
    : _socket{std::move(socket)}
{
}

void Session::setProcessor(std::unique_ptr<IServerProcessor> processor)
{
    _processor = std::move(processor);
}

void Session::start() 
{
    if (!_processor)
    {
        return;
    }
    do_read();
}

void Session::write(const std::string &msg)
{
    do_write(msg);
}

void Session::do_read() 
{
    auto self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_data, max_length),
                            [this, self](const boost::system::error_code &ec, size_t length)
    {
        if (!ec)
        {
            auto str = _processor->parseClientMessage(std::string(_data, length));
            if (!str.empty())
            {
                do_write(str);
            }
        }
    });
}

void Session::do_write(const std::string &msg)
{
    auto self(shared_from_this());
    _socket.async_write_some(boost::asio::buffer(msg),
                             [this, self](const boost::system::error_code &ec, std::size_t /*bytes*/)
    {
        if (!ec)
        {
            do_read();
        }
    });
}
