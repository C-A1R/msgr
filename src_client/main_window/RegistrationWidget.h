#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include "AuthorizationWidget.h"

class RegistrationWidget : public AuthorizationWidget
{
    Q_OBJECT

protected:
    QLineEdit *confirmPassword_lEdit{nullptr};

public:
    explicit RegistrationWidget(const std::shared_ptr<IMsgProcessor> &msgProcessor, QWidget *parent = nullptr);
    void init() override;

private:
    QHBoxLayout *createConfirmLine() override;

private slots:
    void slot_sign_pBtn_clicked() override;
    void slot_SignUp();
};

#endif // REGISTRATIONWINDOW_H
