#ifndef ICLIENTPROCESSOR_H
#define ICLIENTPROCESSOR_H

#include <QObject>

#include <memory>

class UserInfo;
class MessageInfo;

/**
 * @brief интерфейс обработчика запросов/ответов от клиента
 */
class IClientProcessor : public QObject
{
    Q_OBJECT
public:
    IClientProcessor() = default;
    virtual ~IClientProcessor() = default;

    virtual std::shared_ptr<UserInfo> currentUser() const = 0;

    virtual void start() = 0;

    ///запрос на регистрацию учетной записи
    virtual void signUp_request(const QString &login, const QString &password) = 0;
    ///запрос на вход в учетную запись
    virtual void signIn_request(const QString &login, const QString &password) = 0;
    ///запрос на выход из учетной записи
    virtual void signOut_request() = 0;
    ///запрос на получение активных пользователей
    virtual void getUsers_request() = 0;
    ///запрос на получение истории переписки
    virtual void getMessages_request(int contactId, int lastMessageId) = 0;
    ///запрос на отправку сообщения
    virtual void outputMessage_request(int contactId, const std::string &msg) = 0;
    ///ответ на входящее сообщение
    virtual void inputMessage_response(const std::shared_ptr<MessageInfo> &message) = 0;

signals:
    void signal_stopClient();

    ///отправить запрос
    void signal_sendRequest(const std::string &);
    ///отправить ответ
    void signal_sendResponse(const std::string &);

    void signal_signUpResponse(const std::string &);
    void signal_signInResponse(const std::string &);
    void signal_outputMessageResponse(const std::shared_ptr<MessageInfo> &message);
    void signal_getUsersResponse(const std::vector<std::shared_ptr<UserInfo> > &);
    void signal_inputMessageRequest(const std::shared_ptr<MessageInfo> &);
    void signal_newUserRegistered(const std::shared_ptr<UserInfo> &);
    void signal_getMessagesResponse(const std::vector<std::shared_ptr<MessageInfo> > &);

private slots:
    ///обработка всех сообщений от сервера
    virtual void slot_parseRecieved(const std::string &msg) = 0;
};

Q_DECLARE_METATYPE(std::shared_ptr<UserInfo>)
Q_DECLARE_METATYPE(std::vector<std::shared_ptr<UserInfo> >)
Q_DECLARE_METATYPE(std::shared_ptr<MessageInfo>)
Q_DECLARE_METATYPE(std::vector<std::shared_ptr<MessageInfo> >)

#endif // ICLIENTPROCESSOR_H
