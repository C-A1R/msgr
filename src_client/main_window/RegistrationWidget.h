#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include "AuthorizationWidget.h"

/**
 * @brief виджет регистрации пользователя
 */
class RegistrationWidget : public AuthorizationWidget
{
    Q_OBJECT

protected:
    QLineEdit *confirmPassword_lEdit{nullptr};

public:
    explicit RegistrationWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent = nullptr);
    void init() override;

private:
    QHBoxLayout *createConfirmLine() override;

private slots:
    void slot_sign_pBtn_clicked() override;
    ///отправить запрос на регистрацию
    void slot_signUpRequest();
    ///обработка ответа на запрос о регистрации
    void slot_signUpResponse(const std::string &status);
};

#endif // REGISTRATIONWINDOW_H
