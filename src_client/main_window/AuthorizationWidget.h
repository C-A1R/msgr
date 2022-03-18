#ifndef AUTHORIZATIONWIDGET_H
#define AUTHORIZATIONWIDGET_H

#include <QWidget>

#include "client_processor/ClientProcessor.h"
#include "MainWidgets.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;

/**
 * @brief виджет входа в учетную запись пользователя
 */
class AuthorizationWidget : public QWidget
{
    Q_OBJECT

protected:
    QLabel *err_lbl{nullptr};
    QLineEdit *login_lEdit{nullptr};
    QLineEdit *password_lEdit{nullptr};
    QPushButton *sign_pBtn{nullptr};
    QPushButton *changeSign_pBtn{nullptr};

    std::shared_ptr<IClientProcessor> _processor;

public:
    explicit AuthorizationWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent = nullptr);
    virtual void init();

private:
    ///создает (или нет) поле подтверждения пароля
    virtual QHBoxLayout *createConfirmLine() {return nullptr;}

protected:
    ///инициализация пользовательского интерфейса
    void initUi();
    ///отобразить ошибку авторизации
    void showError(const QString &err);

signals:
    ///переклюение между входом и регистрацией пользователя
    void signal_changeSign(MainWidgets);

private slots:
    virtual void slot_sign_pBtn_clicked();
    ///отправить запрос на вход
    void slot_signInRequest();
    ///обработка ответа на запрос входа
    void slot_signInResponse(const std::string &status);
};

#endif // AUTHORIZATIONWIDGET_H
