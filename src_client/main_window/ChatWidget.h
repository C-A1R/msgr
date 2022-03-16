#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

#include "client_processor/ClientProcessor.h"

class QTextEdit;
class QLineEdit;
class QPushButton;

class ChatWidget : public QWidget
{
    Q_OBJECT

    QTextEdit *chat_tEdit{nullptr};
    QLineEdit *msg_lEdit{nullptr};
    QPushButton *send_pBtn{nullptr};

    std::shared_ptr<IClientProcessor> _processor;

public:
    explicit ChatWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent = nullptr);

private:
    void initUi();

private slots:
    void slot_sendMsg();
    void slot_getMsg(const std::string &msg);

};

#endif // CHATWIDGET_H
