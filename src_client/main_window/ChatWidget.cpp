#include "ChatWidget.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
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

void ChatWidget::slot_outputMessageRequest()
{
    _processor->outputMessage_request(msg_lEdit->text().toStdString());
}

void ChatWidget::slot_outputMessageResponse(const std::string &text)
{
    QString html;
    if (!chat_tEdit->toPlainText().isEmpty())
    {
        html = chat_tEdit->toHtml();
    }
    html += QStringLiteral("<h4 align=\"right\"><font color=\"#943126\">%1:</font></h4>")
            .arg(QString::fromStdString(_processor->currentLogin()));
    html += QStringLiteral("<p align=\"right\"><font color=\"#424949\">%1</font></p>")
            .arg(QString::fromStdString(text));

    chat_tEdit->setHtml(html);
    msg_lEdit->clear();
}
