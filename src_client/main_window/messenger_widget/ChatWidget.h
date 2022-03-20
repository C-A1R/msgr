#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

#include <memory>

class QTextEdit;
class QLineEdit;
class QPushButton;
class QStackedWidget;
class UserInfo;
class MessageInfo;

class ChatWidget : public QWidget
{
    Q_OBJECT

    std::shared_ptr<UserInfo> _contact;

    QTextEdit *chat_tEdit{nullptr};
    QLineEdit *msg_lEdit{nullptr};
    QPushButton *send_pBtn{nullptr};

    int lastMessage{-1};

public:
    explicit ChatWidget(const std::shared_ptr<UserInfo> &contact, QWidget *parent = nullptr);
    void writeInputMessage(const std::shared_ptr<MessageInfo> &message);
    void writeOutputMessage(const std::shared_ptr<UserInfo> &currentUser, const std::shared_ptr<MessageInfo> &message);
    int lastMessageId() const { return lastMessage; };
private:
    void initUi();

signals:
    void signalSendMessage(int, const std::string &);
private slots:
    void slot_sendMessage();
};

#endif // CHATWIDGET_H
