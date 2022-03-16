#include "Session.h"

#include <iostream>
#include <string>

Session::Session(tcp::socket socket, std::unique_ptr<IServerProcessor> processor)
    : _socket{std::move(socket)}, _processor{std::move(processor)}
{
}

void Session::start() 
{
    do_read();
}

void Session::do_read() 
{
    auto self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_data, max_length), 
        [this, self](const boost::system::error_code &ec, size_t length)
        {
            if (!ec)
            {
                auto str = std::string(_data, length);
                std::cout << "# READ " << str;
                do_write(_processor->getResponse(str));
            }
    });
}

void Session::do_write(const std::string &msg)
{
//    std::cout << "# WRITE " << msg;
    auto self(shared_from_this());
    _socket.async_write_some(boost::asio::buffer(msg), [this, self](const boost::system::error_code &ec, std::size_t /*bytes*/)
    {
        if (!ec)
        {
//            std::cout << "# " << std::string(_data, length);
            do_read();
        }
    });
}
