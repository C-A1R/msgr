#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include "boost/asio.hpp"

/**
 * @brief асинхронный клиент, непосредственно работает с сокетом
 */
class Client : public QObject
{
    Q_OBJECT

    boost::asio::ip::tcp::socket _socket;
    boost::asio::ip::tcp::resolver _resolver;
    enum {max_length = 1024};
    char _buffer[max_length];
    std::string _bufferLarge;
public:
    Client(boost::asio::io_context &io_context);
    void start(const std::string &host, const std::string &service);
    ///отправка на сервер
    void send(const std::string &msg);
private:
    void do_resolve(const boost::system::error_code &ec, boost::asio::ip::tcp::resolver::iterator it);
    void do_connect(const boost::system::error_code &ec);
    void do_read(const boost::system::error_code &ec, std::size_t bytes);
    void do_read_large(const boost::system::error_code &ec, std::size_t bytes);
    void do_write(const std::string &msg);

signals:
    ///что-то получили от сервера
    void signal_recieved(const std::string &);

public slots:
};

#endif // CLIENT_H
