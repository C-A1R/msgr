#ifndef SERVER_H
#define SERVER_H

#include "Database.h"

#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class Server
{
    tcp::acceptor _acceptor;
    std::shared_ptr<Database> _db{nullptr};
public:
    Server(boost::asio::io_context& io_context, int port);
private:
    void do_accept();
};

#endif //SERVER_H
