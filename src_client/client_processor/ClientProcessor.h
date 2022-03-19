#ifndef CLIENTPROCESSOR_H
#define CLIENTPROCESSOR_H

#include "IClientProcessor.h"
#include "UserInfo.h"

#include <boost/property_tree/ptree.hpp>

#include <memory>

class ClientThread;

using boost::property_tree::ptree;

/**
 * @brief обработчик запросов/ответов от клиента
 */
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
    void signOut_request() override;
    void getUsers_request() override;
    void outputMessage_request(const std::string &msg) override;

private:
    void inputMessage_response(const std::string &text) override;

    ///обработка запросов от сервера
    void parseRequest(const ptree &root);
    ///обработка ответов от сервера
    void parseResponse(const ptree &root);

private slots:
    void slot_parseRecieved(const std::string &msg) override;
};

#endif // CLIENTPROCESSOR_H
