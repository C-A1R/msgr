#ifndef SESSION_H
#define SESSION_H

#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
    tcp::socket _socket;
    enum {max_length = 1024};
    char _data[max_length];
public:
    Session(tcp::socket socket);
    void start();
private:
    void do_read();
    void do_write(const std::string &msg);
};

#endif //SESSION_H
