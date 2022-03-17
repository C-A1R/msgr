#ifndef CLIENTPROCESSOR_H
#define CLIENTPROCESSOR_H

#include "IClientProcessor.h"
#include "UserInfo.h"

#include <memory>

class ClientThread;

class ClientProcessor : public IClientProcessor
{
    std::unique_ptr<ClientThread> _clientThread;
    UserInfo currentUser;

public:
    ClientProcessor();
    ~ClientProcessor();

    std::string currentLogin() const override { return currentUser.login; };

    void start() override;
    void signUp_request(const QString &login, const QString &password) override;
    void signIn_request(const QString &login, const QString &password) override;
    void outputMessage_request(const std::string &msg) override;

private slots:
    void slot_parseResponse(const std::string &response) override;
};

#endif // CLIENTPROCESSOR_H
