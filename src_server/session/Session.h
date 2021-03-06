#ifndef SESSION_H
#define SESSION_H

#include "boost/asio.hpp"

#include "server_processor/ServerProcessor.h"

/**
 * @brief сессия пользователя
 */
class Session : public std::enable_shared_from_this<Session>
{
    boost::asio::ip::tcp::socket _socket;
    enum {max_length = 1024};
    char _buffer[max_length];
    std::string _bufferLarge;
    std::unique_ptr<IServerProcessor> _processor;
public:
    Session(boost::asio::ip::tcp::socket socket);
    void setProcessor(std::unique_ptr<IServerProcessor> processor);
    void start();
    void write(const std::string &msg);
private:
    void do_read();
    void do_write(const std::string &msg);
    void do_write_large(std::string msg);
};

#endif //SESSION_H
