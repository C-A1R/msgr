#ifndef ICLIENTPROCESSOR_H
#define ICLIENTPROCESSOR_H

#include <QObject>

class IClientProcessor : public QObject
{
    Q_OBJECT
public:
    bool _isStarted{false};
    IClientProcessor() = default;
    virtual ~IClientProcessor() = default;

    virtual void start() = 0;
    virtual bool isRunning() const = 0;
    virtual void sendMsg(const std::string &msg) = 0;

    virtual void signUp_request(const QString &login, const QString &password) = 0;
    virtual void signIn_request(const QString &login, const QString &password) = 0;

signals:
    void signal_stopClient();
    void signal_sendToClientThread(const std::string &);
    void signal_sendToGui(const std::string &);

    void signal_sendRequest(const std::string &);

    void signal_signUpResponse(const std::string &);
    void signal_signInResponse(const std::string &);

private slots:
    virtual void slot_getResponse(const std::string &response) = 0;
};

#endif // ICLIENTPROCESSOR_H
