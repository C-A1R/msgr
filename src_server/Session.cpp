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
    _socket.async_read_some(boost::asio::buffer(_buffer, max_length),
                            [this, self](const boost::system::error_code &ec, size_t length)
    {
        if (!ec)
        {
            auto str = _processor->parseClientMessage(std::string(_buffer, length));
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

    if (msg.length() > max_length)
    {
        do_write_large(msg);
        do_read();
    }
    else
    {
        std::cout << "### / do_write " << msg << std::endl;
        _socket.async_write_some(boost::asio::buffer(msg),
                                 [this, self](const boost::system::error_code &ec, std::size_t /*bytes*/)
        {
            if (!ec)
            {
                do_read();
            }
        });
    }
}

void Session::do_write_large(std::string msg)
{
    do_write("#large\n");
    auto byts = _socket.read_some(boost::asio::buffer(_buffer));
    if (std::string(_buffer, byts) != "#ready\n")
    {
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    while (msg.length() > max_length)
    {
        _socket.write_some(boost::asio::buffer(msg.substr(0, max_length)));
        msg = msg.substr(max_length, std::string::npos);
    }
    _socket.write_some(boost::asio::buffer(msg));
}
