#include "SessionManager.h"

#include <algorithm>

SessionManager::SessionManager()
{
}

void SessionManager::addSession(int userId, const std::shared_ptr<Session> &session)
{
    std::lock_guard lock(_mutex);
    _sessions.insert(std::make_pair(userId, session));
    session->start();
}

void SessionManager::removeSession(int userId)
{
    if (userId == -1)
    {
        return;
    }
    std::lock_guard lock(_mutex);
    _sessions.erase(userId);
}

bool SessionManager::isUserOnline(int userId) const
{
    return _sessions.count(userId) > 0;
}

void SessionManager::sendToUser(int userId, const std::string &msg)
{
    if (isUserOnline(userId))
    {
        _sessions.at(userId)->write(msg);
    }
}

void SessionManager::sendToAll(const std::string &msg)
{
    for (const auto &session : _sessions)
    {
        session.second->write(msg);
    }
}
