#include "ChatWidget.h"
#include "UserInfo.h"
#include "MessageInfo.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QShortcut>

#include <QTextFrame>
#include <QTextFormat>

#include <iostream>

ChatWidget::ChatWidget(const std::shared_ptr<UserInfo> &contact, QWidget *parent)
    : QWidget{parent}, _contact{contact}
{

    initUi();
    auto sendShortcut = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    connect(sendShortcut, &QShortcut::activated, this, &ChatWidget::slot_sendMessage);
    connect(send_pBtn, &QPushButton::clicked, this, &ChatWidget::slot_sendMessage);
}

void ChatWidget::writeInputMessage(const std::shared_ptr<MessageInfo> &message)
{
    auto html = QStringLiteral("<h4><font color=\"#943126\">%1:</font></h4>").arg(QString::fromStdString(_contact->username()));
    chat_tEdit->append(html);
    chat_tEdit->setAlignment(Qt::AlignLeft);
    html = QStringLiteral("<p><font color=\"#424949\">%1</font></p>").arg(QString::fromStdString(message->text));
    chat_tEdit->append(html);
    chat_tEdit->setAlignment(Qt::AlignLeft);
    chat_tEdit->textCursor().movePosition(QTextCursor::End);
    lastMessage = message->id;
}

void ChatWidget::writeOutputMessage(const std::shared_ptr<UserInfo> &currentUser, const std::shared_ptr<MessageInfo> &message)
{
    auto html = QStringLiteral("<h4><font color=\"#239B56\">%1:</font></h4>").arg(QString::fromStdString(currentUser->username()));
    chat_tEdit->append(html);
    chat_tEdit->setAlignment(Qt::AlignRight);
    html = QStringLiteral("<p><font color=\"#424949\">%1</font></p>").arg(QString::fromStdString(message->text));
    chat_tEdit->append(html);
    chat_tEdit->setAlignment(Qt::AlignRight);
    chat_tEdit->textCursor().movePosition(QTextCursor::End);
    msg_lEdit->clear();
    lastMessage = message->id;
}

void ChatWidget::initUi()
{
    chat_tEdit = new QTextEdit(this);
    chat_tEdit->setReadOnly(true);

    msg_lEdit = new QLineEdit(this);
    send_pBtn = new QPushButton(QStringLiteral("Send"), this);
    auto send_hLay = new QHBoxLayout();
    send_hLay->addWidget(msg_lEdit);
    send_hLay->addWidget(send_pBtn);

    auto main_vLay = new QVBoxLayout();
    main_vLay->setMargin(0);
    main_vLay->addWidget(chat_tEdit);
    main_vLay->addLayout(send_hLay);
    setLayout(main_vLay);
}

void ChatWidget::slot_sendMessage()
{
    emit signalSendMessage(_contact->id, msg_lEdit->text().toStdString());
}
