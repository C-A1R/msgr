#ifndef SERVER_H
#define SERVER_H

#include "database/Database.h"

#include "boost/asio.hpp"

#include <map>

using boost::asio::ip::tcp;

class SessionManager;

/**
 * @brief асинхронный сервер
 */
class Server
{
    tcp::acceptor _acceptor;
    std::shared_ptr<IDatabase> _db{nullptr};
    std::shared_ptr<SessionManager> _sessionManager;

public:
    Server(boost::asio::io_context& io_context, int port);
private:
    void do_accept();
};

#endif //SERVER_H
