#ifndef CLIENTPROCESSOR_H
#define CLIENTPROCESSOR_H

#include "IClientProcessor.h"

#include <boost/property_tree/ptree.hpp>

class UserInfo;
class ClientThread;

using boost::property_tree::ptree;

/**
 * @brief обработчик запросов/ответов от клиента
 */
class ClientProcessor : public IClientProcessor
{
    std::unique_ptr<ClientThread> _clientThread;
    std::shared_ptr<UserInfo> _currentUser;

public:
    ClientProcessor();
    ~ClientProcessor();

    std::shared_ptr<UserInfo> currentUser() const override;

    void start() override;
    void signUp_request(const QString &login, const QString &password) override;
    void signIn_request(const QString &login, const QString &password) override;
    void signOut_request() override;
    void getUsers_request() override;
    void getMessages_request(int contactId, int lastMessageId) override;
    void outputMessage_request(int contactId, const std::string &msg) override;

private:
    void inputMessage_response(const std::shared_ptr<MessageInfo> &message) override;

    ///обработка запросов от сервера
    void parseRequest(const ptree &root);
    ///обработка ответов от сервера
    void parseResponse(const ptree &root);

private slots:
    void slot_parseRecieved(const std::string &msg) override;
};

#endif // CLIENTPROCESSOR_H
