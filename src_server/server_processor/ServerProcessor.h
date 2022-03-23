#ifndef SERVERPROCESSOR_H
#define SERVERPROCESSOR_H

#include "IServerProcessor.h"

#include <boost/property_tree/ptree.hpp>

#include <memory>

class Session;
class SessionManager;
class IDatabase;
class Request;
class Response;

using boost::property_tree::ptree;

/**
 * @brief обработчик запросов/ответов от клиента
 */
class ServerProcessor : public IServerProcessor
{
    std::shared_ptr<IDatabase> _db;
    std::shared_ptr<SessionManager> _sessionMgr;
    std::shared_ptr<Session> _currentSession;

public:
    ServerProcessor(const std::shared_ptr<IDatabase> &db,
                    const std::shared_ptr<SessionManager> &sessionMgr,
                    const std::shared_ptr<Session> &currentSession);

    std::string parseClientMessage(const std::string &msg) const override;

private:
    ///обработка запросов от клиента
    std::string parseRequest(const Request &request) const;
    ///обработка ответов от клиента
    std::string parseResponse(const Response &response) const;

    ///регистрация
    std::string signUp(const Request &request) const;
    ///вход
    std::string signIn(const Request &request) const;
    ///выход
    std::string signOut(const Request &request) const;
    ///достать всех пользователей
    std::string allUsers() const;
    ///исходящее сообщение от клиента
    std::string outputMessage(const Request &request) const;
    ///входящее сообщение клиенту
    std::string inputMessage(const Response &response) const;
    ///получить переписку двух пользователей
    std::string getMessages(const Request &request) const;
};

#endif // SERVERPROCESSOR_H
