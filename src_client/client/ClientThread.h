#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>

#include "Client.h"

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
    void signal_sendToClient(const QString &msg);
    void signal_getFromThread(const QString &msg);

public slots:
    void slot_stopClient();
};

#endif // CLIENTTHREAD_H
