#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "boost/asio.hpp"

#include <string>


using boost::asio::ip::tcp;

class Client : public QObject
{
    Q_OBJECT

    tcp::socket _socket;
    tcp::resolver _resolver;
    char _buffer[4096];
public:
    Client(boost::asio::io_context &io_context);
    void start(const std::string &host, const std::string &service);
private:
    void resolveHandler(const boost::system::error_code &ec, tcp::resolver::iterator it);
    void connectHandler(const boost::system::error_code &ec);
    void readHandler(const boost::system::error_code &ec, std::size_t bytes);
    void writeHandler(const std::string &msg);

signals:
    void signal_getFromServer(const std::string &);

public slots:
    void slot_sendToServer(const std::string &request);
};

#endif // CLIENT_H
