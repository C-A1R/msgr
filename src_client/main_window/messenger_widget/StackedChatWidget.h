#ifndef STACKEDCHATWIDGET_H
#define STACKEDCHATWIDGET_H

#include <QWidget>

#include <memory>

class ChatWidget;
class QStackedWidget;
class UserInfo;
class MessageInfo;

class StackedChatWidget : public QWidget
{
    Q_OBJECT
    std::unordered_map<int, ChatWidget *> _contacts;
    QStackedWidget *_stack {nullptr};
public:
    StackedChatWidget(QWidget *parent = nullptr);
    void addChat(const std::shared_ptr<UserInfo> &contact);
    void writeOutputMessage(const std::shared_ptr<UserInfo> &currentUser, const std::shared_ptr<MessageInfo> &message);
    void writeInputMessage(const std::shared_ptr<MessageInfo> &message);
    void showChat(int contactId);
    int lastMessageId(int contactId) const;
private:
    void initUi();

signals:
    void signalSendMessage(int, const std::string &);
};

#endif // STACKEDCHATWIDGET_H
