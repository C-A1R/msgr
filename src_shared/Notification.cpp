#include "Notification.h"
#include "UserInfo.h"
#include "MessageInfo.h"

#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;

Notification &Notification::writeSignUser(const std::string &login, const std::string &password)
{
    _root.put("user.login", login);
    _root.put("user.password", password);
    return *this;
}

Notification &Notification::writeUser(int id, const std::string &login, const std::string &name)
{
    _root.put("user.id", id);
    _root.put("user.login", login);
    _root.put("user.name", name);
    return *this;
}

Notification &Notification::writeUsers(const std::vector<UserInfo> &users)
{
    ptree children;
    for (const auto &user : users)
    {
        ptree child;
        child.put("id", user.id);
        child.put("login", user.login);
        child.put("name", user.name);
        children.push_back(std::make_pair("", child));
    }
    _root.add_child("users", children);
    return *this;
}

Notification &Notification::writeMessage(int id, int sender, int recipient, const std::string &text)
{
    _root.put("message.id", id);
    _root.put("message.sender", sender);
    _root.put("message.recipient", recipient);
    _root.put("message.text", text);
    return *this;
}

Notification &Notification::writeMessage(const std::shared_ptr<MessageInfo> &message)
{
    return writeMessage(message->id, message->senderId, message->recipientId, message->text);
}

Notification &Notification::writeMessages(const std::vector<MessageInfo> &messages)
{
    ptree children;
    for (const auto &msg : messages)
    {
        ptree child;
        child.put("id", msg.id);
        child.put("sender", msg.senderId);
        child.put("recipient", msg.recipientId);
        child.put("text", msg.text);
        children.push_back(std::make_pair("", child));
    }
    _root.add_child("messages", children);
    return *this;
}

std::string Notification::toJson()
{
    std::stringstream stream;
    boost::property_tree::write_json(stream, _root);
    return stream.str() + '\n';
}

NotificationType Notification::readNotificationType(const std::string &str)
{
    ptree root;
    std::stringstream stream(str);
    boost::property_tree::read_json(stream, root);

    if (root.count("response_type") > 0)
    {
        return NotificationType::type_response;
    }
    else if (root.count("request_type") > 0)
    {
        return NotificationType::type_request;
    }
    else
        return NotificationType::type_invalid;
}

std::string Notification::type() const
{
    return _root.get<std::string>(type_tag());
}

std::pair<std::string, std::string> Notification::readSignUser() const
{
    return std::make_pair(_root.get<std::string>("user.login"),
                          _root.get<std::string>("user.password"));
}

std::shared_ptr<UserInfo> Notification::readUser() const
{
    auto user = std::make_shared<UserInfo>();
    user->id = _root.get<int>("user.id");
    user->login = _root.get<std::string>("user.login");
    user->name = _root.get<std::string>("user.name");
    return user;
}

std::vector<std::shared_ptr<UserInfo> > Notification::readUsers() const
{
    std::vector<std::shared_ptr<UserInfo> > users;
    auto usersRoot = _root.get_child("users");
    for (const auto &u : usersRoot)
    {
        auto user = std::make_shared<UserInfo>();
        user->id = u.second.get<int>("id");
        user->login = u.second.get<std::string>("login");
        user->name = u.second.get<std::string>("name");
        users.push_back(user);
    }
    return users;
}

std::shared_ptr<MessageInfo> Notification::readMessage() const
{
    auto message = std::make_shared<MessageInfo>();
    message->id = _root.get<int>("message.id");
    message->senderId = _root.get<int>("message.sender");
    message->recipientId = _root.get<int>("message.recipient");
    message->text = _root.get<std::string>("message.text");
    return message;
}

std::vector<std::shared_ptr<MessageInfo> > Notification::readMessages() const
{
    std::vector<std::shared_ptr<MessageInfo> > messages;
    auto messagesRoot = _root.get_child("messages");
    for (const auto &m : messagesRoot)
    {
        auto msg = std::make_shared<MessageInfo>();
        msg->id = m.second.get<int>("id");
        msg->senderId = m.second.get<int>("sender");
        msg->recipientId = m.second.get<int>("recipient");
        msg->text = m.second.get<std::string>("text");
        messages.push_back(msg);
    }
    return messages;
}

Request::Request(const std::string &requestType)
{
    _root.put(Request::type_tag(), requestType);
}

Request::Request(const boost::property_tree::ptree &root)
{
    _root = root;
}

Request Request::fromJson(const std::string &str)
{
    ptree root;
    std::stringstream stream(str);
    boost::property_tree::read_json(stream, root);
    return Request(root);
}



Response::Response(const std::string &responseType)
{
    _root.put(Response::type_tag(), responseType);
}

Response::Response(const boost::property_tree::ptree &root)
{
    _root = root;
}

Response Response::fromJson(const std::string &str)
{
    ptree root;
    std::stringstream stream(str);
    boost::property_tree::read_json(stream, root);
    return Response(root);
}

Response &Response::writeStatusOk()
{
    _root.put("status", ok());
    return *this;
}

Response &Response::writeStatus(const std::string &status)
{
    _root.put("status", status);
    return *this;
}

std::string Response::status() const
{
    return _root.get<std::string>("status");
}

std::string Response::errResponse()
{
    return Response("error").toJson();
}
