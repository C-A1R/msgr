#ifndef IMSGPROCESSOR_H
#define IMSGPROCESSOR_H

#include <QObject>

class IMsgProcessor : public QObject
{
    Q_OBJECT
public:
    IMsgProcessor() = default;
    virtual ~IMsgProcessor() = default;

    virtual void start() = 0;
    virtual void sendMsg(const QString &msg) = 0;

    virtual void signUp_request(const QString &login, const QString &password) = 0;

signals:
    void signal_stopClient();
    void signal_sendToClientThread(const QString &msg);
    void signal_sendToGui(const QString &msg);

    void signal_sendRequest(const QString &);
};

#endif // IMSGPROCESSOR_H
