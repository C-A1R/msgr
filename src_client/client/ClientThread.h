#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>

#include "Client.h"

/**
 * @brief поток для взаимодействия с сервером
 */
class ClientThread : public QThread
{
    Q_OBJECT
    boost::asio::io_context _io_context;
    std::unique_ptr<Client> _client;
public:
    ClientThread();
    ~ClientThread();
protected:
    void run();

signals:
    ///что-то получили от сервера
    void signal_recieved(const std::string &);

public slots:
    void slot_stopClient();
    ///отправка на сервер
    void slot_send(const std::string &msg);
};

#endif // CLIENTTHREAD_H
