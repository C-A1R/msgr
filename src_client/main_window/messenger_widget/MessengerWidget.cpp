#include "MessengerWidget.h"
#include "StackedChatWidget.h"
#include "../../../src_shared/UserInfo.h"
#include "../../../src_shared/MessageInfo.h"

#include <QListWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QString>

#include <iostream>

MessengerWidget::MessengerWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent)
    : QWidget{parent}, _processor{processor}
{
    initUi();
    connect(contacts_listWidget, &QListWidget::currentItemChanged, this, &MessengerWidget::slot_changeChat);
    connect(chats_widget, &StackedChatWidget::signalSendMessage, this, &MessengerWidget::slot_outputMessageRequest);
    connect(_processor.get(), &IClientProcessor::signal_outputMessageResponse, this, &MessengerWidget::slot_outputMessageResponse);
    connect(_processor.get(), &IClientProcessor::signal_inputMessageRequest, this, &MessengerWidget::slot_inputMessageRequest);
    connect(_processor.get(), &IClientProcessor::signal_getUsersResponse, this, &MessengerWidget::slot_getUsersResponse);
    connect(_processor.get(), &IClientProcessor::signal_newUserRegistered, this, &MessengerWidget::slot_newUserRegistered);
    connect(_processor.get(), &IClientProcessor::signal_getMessagesResponse, this, &MessengerWidget::slot_getMessagesResponse);
}

MessengerWidget::~MessengerWidget()
{
    _processor->signOut_request();
}

void MessengerWidget::initUi()
{
    contacts_listWidget = new QListWidget(this);
    chats_widget = new StackedChatWidget(this);
    auto splitter = new QSplitter(this);
    splitter->addWidget(contacts_listWidget);
    splitter->addWidget(chats_widget);
    splitter->setSizes(QList<int>() << 50 << 350);
    auto main_vLay = new QVBoxLayout();
    main_vLay->addWidget(splitter);
    setLayout(main_vLay);
}

void MessengerWidget::addContact(const std::shared_ptr<UserInfo> &contact)
{
    auto item = new QListWidgetItem(QString::fromStdString(contact->name.empty() ? contact->login : contact->name));
    item->setData(Qt::UserRole, contact->id);
    contacts_listWidget->addItem(item);
    chats_widget->addChat(contact);
}

void MessengerWidget::slot_outputMessageRequest(int contactId, const std::string &text)
{
    _processor->outputMessage_request(contactId, text);
}

void MessengerWidget::slot_outputMessageResponse(const std::shared_ptr<MessageInfo> &message)
{
    chats_widget->writeOutputMessage(_processor->currentUser(), message);
}

void MessengerWidget::slot_inputMessageRequest(const std::shared_ptr<MessageInfo> &message)
{
    chats_widget->writeInputMessage(message);
    _processor->inputMessage_response(message);
}

void MessengerWidget::slot_getUsersResponse(const std::vector<std::shared_ptr<UserInfo> > &contacts)
{
    contacts_listWidget->clear();
    for (const auto &contact : contacts)
    {
        addContact(contact);
    }
    if (contacts_listWidget->count())
    {
        contacts_listWidget->setCurrentRow(0);
    }
}

void MessengerWidget::slot_newUserRegistered(const std::shared_ptr<UserInfo> &contact)
{
    addContact(contact);
    if (contacts_listWidget->count())
    {
        contacts_listWidget->setCurrentRow(0);
    }
}

void MessengerWidget::slot_getMessagesResponse(const std::vector<std::shared_ptr<MessageInfo> > &messages)
{
    for (const auto &msg : messages)
    {
        if (msg->senderId == _processor->currentUser()->id)
        {
            chats_widget->writeOutputMessage(_processor->currentUser(), msg);
        }
        else
        {
            chats_widget->writeInputMessage(msg);
        }
    }
}

void MessengerWidget::slot_changeChat()
{
    auto contactId = contacts_listWidget->currentItem()->data(Qt::UserRole).toInt();
    chats_widget->showChat(contactId);
    _processor->getMessages_request(contactId, chats_widget->lastMessageId(contactId));
}

void MessengerWidget::updateContactList()
{
    _processor->getUsers_request();
}
