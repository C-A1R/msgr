#ifndef CLIENTPROCESSOR_H
#define CLIENTPROCESSOR_H

#include "IClientProcessor.h"
#include <memory>

class ClientThread;

class ClientProcessor : public IClientProcessor
{
//    Q_OBJECT
    std::unique_ptr<ClientThread> _clientThread;
public:
    ClientProcessor();
    ~ClientProcessor();

    void start() override;
    void sendMsg(const QString &msg) override;

    void signUp_request(const QString &login, const QString &password) override;

private slots:
    void slot_getMsg(const QString &msg);
};

#endif // CLIENTPROCESSOR_H
