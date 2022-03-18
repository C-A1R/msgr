#ifndef ICLIENTPROCESSOR_H
#define ICLIENTPROCESSOR_H

#include <QObject>

/**
 * @brief интерфейс обработчика запросов/ответов от клиента
 */
class IClientProcessor : public QObject
{
    Q_OBJECT
public:
    IClientProcessor() = default;
    virtual ~IClientProcessor() = default;

    virtual std::string currentLogin() const = 0;

    virtual void start() = 0;

    ///запрос на регистрацию учетной записи
    virtual void signUp_request(const QString &login, const QString &password) = 0;
    ///запрос на вход в учетную запись
    virtual void signIn_request(const QString &login, const QString &password) = 0;
    ///запрос на выход из учетной записи
    virtual void signOut_request() = 0;
    ///запрос на отправку сообщения
    virtual void outputMessage_request(const std::string &msg) = 0;

    virtual void inputMessage_response(const std::string &text) = 0;

signals:
    void signal_stopClient();

    ///отправить запрос
    void signal_sendRequest(const std::string &);
    ///отправить ответ
    void signal_sendResponse(const std::string &);

    void signal_signUpResponse(const std::string &);
    void signal_signInResponse(const std::string &);
    void signal_outputMessageResponse(const std::string &);

    void signal_inputMessageRequest(const std::string &, const std::string &);

private slots:
    ///обработка всех сообщений от сервера
    virtual void slot_parseRecieved(const std::string &msg) = 0;
};

#endif // ICLIENTPROCESSOR_H
