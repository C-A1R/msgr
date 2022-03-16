#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

#include "message_processor/MsgProcessor.h"

class QTextEdit;
class QLineEdit;
class QPushButton;

class ChatWidget : public QWidget
{
    Q_OBJECT

    QTextEdit *chat_tEdit{nullptr};
    QLineEdit *msg_lEdit{nullptr};
    QPushButton *send_pBtn{nullptr};

    std::shared_ptr<IMsgProcessor> _msgProcessor;

public:
    explicit ChatWidget(const std::shared_ptr<IMsgProcessor> &msgProcessor, QWidget *parent = nullptr);

private:
    void initUi();

private slots:
    void slot_sendMsg();
    void slot_getMsg(const QString &msg);

};

#endif // CHATWIDGET_H
