#include "ChatWidget.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtDebug>

ChatWidget::ChatWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent)
    : QWidget{parent}, _processor{processor}
{
    initUi();
    connect(send_pBtn, &QPushButton::clicked, this, &ChatWidget::slot_sendMsg);

    connect(_processor.get(), &IClientProcessor::signal_sendToGui, this, &ChatWidget::slot_getMsg);
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
    main_vLay->addWidget(chat_tEdit);
    main_vLay->addLayout(send_hLay);

    setLayout(main_vLay);
}

void ChatWidget::slot_sendMsg()
{
    _processor->sendMsg(msg_lEdit->text());
}

void ChatWidget::slot_getMsg(const QString &msg)
{
    if (msg == QStringLiteral("pong\n"))
    {
        qDebug() << "pong";
        return;
    }

    chat_tEdit->setText(chat_tEdit->toPlainText() + msg);
    msg_lEdit->clear();
}
