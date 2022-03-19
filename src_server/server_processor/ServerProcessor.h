#ifndef SERVERPROCESSOR_H
#define SERVERPROCESSOR_H

#include "IServerProcessor.h"
#include "../database/Database.h"

#include <boost/property_tree/ptree.hpp>

#include <memory>
#include <map>

class Session;
class SessionManager;

using boost::property_tree::ptree;

/**
 * @brief обработчик запросов/ответов от клиента
 */
class ServerProcessor : public IServerProcessor
{
    std::shared_ptr<IDatabase> _db;
    std::shared_ptr<SessionManager> _sessionMgr;
    int _currentUser{-1};
    std::shared_ptr<Session> _currentSession;
    const std::string errResponse = "{\n    \"response_type\": \"error\"\n}\n";

public:
    ServerProcessor(const std::shared_ptr<IDatabase> &db,
                    const std::shared_ptr<SessionManager> &sessionMgr,
                    const std::shared_ptr<Session> &currentSession);

    std::string parseClientMessage(const std::string &msg) override;

private:
    ///обработка запросов от клиента
    std::string parseRequest(const ptree &root);
    ///обработка ответов от клиента
    std::string parseResponse(const ptree &root);

    ///регистрация
    std::string signUp(const ptree &requestRoot);
    ///вход
    std::string signIn(const ptree &requestRoot);
    ///выход
    std::string signOut();
    ///достать всех пользователей
    std::string allUsers();
    ///исходящее сообщение от клиента
    std::string outputMessage(const ptree &root);
    ///входящее сообщение клиенту
    std::string inputMessage(const ptree &root);
};

#endif // SERVERPROCESSOR_H
