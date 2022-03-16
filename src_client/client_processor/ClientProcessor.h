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
    void sendMsg(const std::string &msg) override;

    void signUp_request(const QString &login, const QString &password) override;

private slots:
    void slot_getResponse(const std::string &response) override;
};

#endif // CLIENTPROCESSOR_H
