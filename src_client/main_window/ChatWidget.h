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
    void slot_outputMessageRequest();
    void slot_outputMessageResponse(const std::string &text);

};

#endif // CHATWIDGET_H
