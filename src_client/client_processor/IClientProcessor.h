#ifndef ICLIENTPROCESSOR_H
#define ICLIENTPROCESSOR_H

#include <QObject>

/**
 * @brief интерфейс, отвечающий за работу с запросами/ответами
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
    ///запрос на отправку сообщения
    virtual void outputMessage_request(const std::string &msg) = 0;

signals:
    void signal_stopClient();

    ///отправить запрос
    void signal_sendRequest(const std::string &);

    void signal_signUpResponse(const std::string &);
    void signal_signInResponse(const std::string &);
    void signal_outputMessageResponse(const std::string &);

private slots:
    ///обработка ответов
    virtual void slot_parseResponse(const std::string &response) = 0;
};

#endif // ICLIENTPROCESSOR_H
