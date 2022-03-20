#ifndef MESSENGERWIDGET_H
#define MESSENGERWIDGET_H

#include <QWidget>

#include "client_processor/ClientProcessor.h"

class QListWidget;
class ChatWidget;
class StackedChatWidget;

/**
 * @brief виджет самого мессенджера
 */
class MessengerWidget : public QWidget
{
    Q_OBJECT

    QListWidget *contacts_listWidget{nullptr};
    StackedChatWidget *chats_widget {nullptr};
    std::shared_ptr<IClientProcessor> _processor;

public:
    explicit MessengerWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent = nullptr);
    ~MessengerWidget();

private:
    ///инициализация пользовательского интерфейса
    void initUi();
    void addContact(const std::shared_ptr<UserInfo> &contact);

private slots:
    ///отправка исходящего сообщения
    void slot_outputMessageRequest(int contactId, const std::string &text);
    ///получение ответа на исходящее сообщения (результат отправки)
    void slot_outputMessageResponse(const std::shared_ptr<MessageInfo> &message);
    ///получение входящего сообщения и отправка ответа на него (результат получения)
    void slot_inputMessageRequest(const std::shared_ptr<MessageInfo> &message);
    ///получение ответа на запрос контактов
    void slot_getUsersResponse(const std::vector<std::shared_ptr<UserInfo> > &contacts);
    ///новый пользователь зарегался
    void slot_newUserRegistered(const std::shared_ptr<UserInfo> &contact);
    ///получение ответа на запрос переписки
    void slot_getMessagesResponse(const std::vector<std::shared_ptr<MessageInfo> > &messages);

    void slot_changeChat();

public slots:
    void updateContactList();
};

#endif // MESSENGERWIDGET_H
