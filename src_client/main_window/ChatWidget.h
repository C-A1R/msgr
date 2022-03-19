#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

#include "client_processor/ClientProcessor.h"

class QListWidget;
class QTextEdit;
class QLineEdit;
class QPushButton;

/**
 * @brief виджет переписки
 */
class ChatWidget : public QWidget
{
    Q_OBJECT

    QListWidget *contacts_listWidget{nullptr};
    QTextEdit *chat_tEdit{nullptr};
    QLineEdit *msg_lEdit{nullptr};
    QPushButton *send_pBtn{nullptr};

    std::shared_ptr<IClientProcessor> _processor;

public:
    explicit ChatWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent = nullptr);
    ~ChatWidget();

private:
    ///инициализация пользовательского интерфейса
    void initUi();

private slots:
    ///отправка исходящего сообщения
    void slot_outputMessageRequest();
    ///получение ответа на исходящее сообщения (результат отправки)
    void slot_outputMessageResponse(const std::string &text);
    ///получение входящего сообщения и отправка ответа на него (результат получения)
    void slot_inputMessageRequest(const std::string &sender, const std::string &text);
    ///получение ответа на запрос контактов
    void slot_getUsersResponse(const std::vector<UserInfo> contacts);

public slots:
    void updateContactList();
};

#endif // CHATWIDGET_H
