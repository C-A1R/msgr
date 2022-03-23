#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "Session.h"

#include <unordered_map>
#include <mutex>

/**
 * @brief учет и взаимодействие подключенных пользователей
 */
class SessionManager
{
    std::unordered_map<int, std::shared_ptr<Session> > _sessions;
    std::mutex _mutex;
public:
    SessionManager();
    void addSession(int userId, const std::shared_ptr<Session> &session);
    void removeSession(int userId);
    bool isUserOnline(int userId) const;
    void sendToUser(int userId, const std::string &msg);
    void sendToAll(const std::string &msg);
};

#endif // SESSIONMANAGER_H
