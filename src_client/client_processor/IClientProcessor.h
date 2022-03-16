#ifndef ICLIENTPROCESSOR_H
#define ICLIENTPROCESSOR_H

#include <QObject>

class IClientProcessor : public QObject
{
    Q_OBJECT
public:
    IClientProcessor() = default;
    virtual ~IClientProcessor() = default;

    virtual void start() = 0;
    virtual void sendMsg(const QString &msg) = 0;

    virtual void signUp_request(const QString &login, const QString &password) = 0;

signals:
    void signal_stopClient();
    void signal_sendToClientThread(const QString &msg);
    void signal_sendToGui(const QString &msg);

    void signal_sendRequest(const QString &);
};

#endif // ICLIENTPROCESSOR_H
