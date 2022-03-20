#ifndef SERVER_H
#define SERVER_H

#include "boost/asio.hpp"

using boost::asio::ip::tcp;

class SessionManager;
class IDatabase;

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
