#include "ChatWidget.h"

#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSplitter>
#include <QString>
#include <QShortcut>

#include <iostream>

ChatWidget::ChatWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent)
    : QWidget{parent}, _processor{processor}
{
    initUi();
    auto sendShortcut = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    connect(sendShortcut, &QShortcut::activated, this, &ChatWidget::slot_outputMessageRequest);
    connect(send_pBtn, &QPushButton::clicked, this, &ChatWidget::slot_outputMessageRequest);
    connect(_processor.get(), &IClientProcessor::signal_outputMessageResponse, this, &ChatWidget::slot_outputMessageResponse);
    connect(_processor.get(), &IClientProcessor::signal_inputMessageRequest, this, &ChatWidget::slot_inputMessageRequest);
    connect(_processor.get(), &IClientProcessor::signal_getUsersResponse, this, &ChatWidget::slot_getUsersResponse);
}

ChatWidget::~ChatWidget()
{
    _processor->signOut_request();
}

void ChatWidget::initUi()
{
    contacts_listWidget = new QListWidget(this);

    auto chat_widget = new QWidget();
    {
        chat_tEdit = new QTextEdit(this);
        chat_tEdit->setReadOnly(true);

        msg_lEdit = new QLineEdit(this);
        send_pBtn = new QPushButton(QStringLiteral("Send"), this);
        auto send_hLay = new QHBoxLayout();
        send_hLay->addWidget(msg_lEdit);
        send_hLay->addWidget(send_pBtn);

        auto chat_vLay = new QVBoxLayout();
        chat_vLay->setMargin(0);
        chat_vLay->addWidget(chat_tEdit);
        chat_vLay->addLayout(send_hLay);
        chat_widget->setLayout(chat_vLay);
    }

    auto splitter = new QSplitter(this);
    splitter->addWidget(contacts_listWidget);
    splitter->addWidget(chat_widget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);

    auto main_vLay = new QVBoxLayout();
    main_vLay->addWidget(splitter);
    setLayout(main_vLay);
}

void ChatWidget::slot_outputMessageRequest()
{
    _processor->outputMessage_request(msg_lEdit->text().toStdString());
}

void ChatWidget::slot_outputMessageResponse(const std::string &text)
{
    QString html;
    html += QStringLiteral("<h4 align=\"right\"><font color=\"#943126\">%1:</font></h4>")
            .arg(QString::fromStdString(_processor->currentLogin()));
    html += QStringLiteral("<p align=\"right\"><font color=\"#424949\">%1</font></p>")
            .arg(QString::fromStdString(text));
    chat_tEdit->append(html);
    msg_lEdit->clear();
}

void ChatWidget::slot_inputMessageRequest(const std::string &sender, const std::string &text)
{
    QString html;
    html += QStringLiteral("<h4 align=\"left\"><font color=\"#943126\">%1:</font></h4>")
            .arg(QString::fromStdString(sender));
    html += QStringLiteral("<p align=\"left\"><font color=\"#424949\">%1</font></p>")
            .arg(QString::fromStdString(text));
    chat_tEdit->append(html);
    _processor->inputMessage_response(text);
}

void ChatWidget::slot_getUsersResponse(const std::vector<UserInfo> contacts)
{
    for (const auto &user : contacts)
    {
        contacts_listWidget->addItem(QString::fromStdString(user.login));
    }
}

void ChatWidget::updateContactList()
{
    _processor->getUsers_request();
}
