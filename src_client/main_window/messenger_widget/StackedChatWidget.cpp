#include "StackedChatWidget.h"
#include "ChatWidget.h"
#include "UserInfo.h"
#include "MessageInfo.h"

#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>

#include <iostream>

StackedChatWidget::StackedChatWidget(QWidget *parent) : QWidget(parent)
{
    initUi();
}

void StackedChatWidget::addChat(const std::shared_ptr<UserInfo> &contact)
{
    if (_contacts.count(contact->id) > 0)
        return;
    auto chat = new ChatWidget(contact, _stack);
    connect(chat, &ChatWidget::signalSendMessage, this, &StackedChatWidget::signalSendMessage);
    _stack->addWidget(chat);
    _contacts.insert(std::make_pair(contact->id, chat));
}

void StackedChatWidget::writeOutputMessage(const std::shared_ptr<UserInfo> &currentUser, const std::shared_ptr<MessageInfo> &message)
{
    if (!_contacts.count(message->recipientId))
        return;
    _contacts.at(message->recipientId)->writeOutputMessage(currentUser, message);
}

void StackedChatWidget::writeInputMessage(const std::shared_ptr<MessageInfo> &message)
{
    if (!_contacts.count(message->senderId))
        return;
    _contacts.at(message->senderId)->writeInputMessage(message);
}

void StackedChatWidget::initUi()
{
    _stack = new QStackedWidget(this);
    auto main_vLay = new QVBoxLayout();
    main_vLay->setMargin(0);
    main_vLay->addWidget(_stack);
    setLayout(main_vLay);
}

void StackedChatWidget::showChat(int contactId)
{
    if (!_contacts.count(contactId))
        return;
    _stack->setCurrentWidget(_contacts.at(contactId));
}

int StackedChatWidget::lastMessageId(int contactId) const
{
    if (!_contacts.count(contactId))
        return -1;
    return _contacts.at(contactId)->lastMessageId();
}
