#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <boost/property_tree/ptree.hpp>

class UserInfo;
class MessageInfo;

enum class NotificationType
{
    type_invalid,
    type_request,
    type_response
};

class Notification
{
protected:
    boost::property_tree::ptree _root;
    Notification() = default;
    virtual ~Notification() = default;

public:
    Notification &writeSignUser(const std::string &login, const std::string &password);
    Notification &writeUser(int id, const std::string &login, const std::string &name);
    Notification &writeUsers(const std::vector<UserInfo> &users);
    Notification &writeMessage(int id, int sender, int recipient, const std::string &text);
    Notification &writeMessage(const std::shared_ptr<MessageInfo>&message);
    Notification &writeMessages(const std::vector<MessageInfo> &messages);
    template <typename T>
    Notification &writeValue(const std::string &name, const T &value)
    {
        _root.put(name, value);
        return *this;
    }

    std::string toJson();
    static NotificationType readNotificationType(const std::string &str);
    std::string type() const;

    std::pair<std::string, std::string> readSignUser() const;
    std::shared_ptr<UserInfo> readUser() const;
    std::vector<std::shared_ptr<UserInfo> > readUsers() const;
    std::shared_ptr<MessageInfo> readMessage() const;
    std::vector<std::shared_ptr<MessageInfo> > readMessages() const;
    template <typename T>
    T readValue(const std::string &name) const
    {
        return _root.get<T>(name);
    }

private:
    virtual std::string type_tag() const = 0;
};


class Request : public Notification
{
public:
    Request(const std::string &requestType);
    Request(const boost::property_tree::ptree &root);
    static Request fromJson(const std::string &str);

private:
    std::string type_tag() const override { return "request_type"; }
};


class Response : public Notification
{
public:
    Response(const std::string &responseType);
    Response(const boost::property_tree::ptree &root);
    static Response fromJson(const std::string &str);
    Response &writeStatusOk();
    Response &writeStatus(const std::string &status);

    std::string status() const;

    static std::string ok() { return "ok"; }
    static std::string errResponse();

private:
    std::string type_tag() const override { return "response_type"; }
};

#endif // NOTIFICATION_H
