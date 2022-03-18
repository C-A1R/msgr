#include "RegistrationWidget.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

RegistrationWidget::RegistrationWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent)
    : AuthorizationWidget{processor, parent}
{
}

void RegistrationWidget::init()
{
    initUi();
    sign_pBtn->setText(QStringLiteral("Sign up"));
    changeSign_pBtn->setText(QStringLiteral("Sign in your account"));
    connect(sign_pBtn, &QPushButton::clicked, this, &RegistrationWidget::slot_signUpRequest);
    connect(_processor.get(), &IClientProcessor::signal_signUpResponse, this, &RegistrationWidget::slot_signUpResponse);
}

QHBoxLayout *RegistrationWidget::createConfirmLine()
{
    confirmPassword_lEdit = new QLineEdit(this);
    confirmPassword_lEdit->setPlaceholderText(QStringLiteral("Confirm password"));
    confirmPassword_lEdit->setEchoMode(QLineEdit::Password);
    auto confirmPassword_hLay = new QHBoxLayout();
    confirmPassword_hLay->addStretch();
    confirmPassword_hLay->addWidget(confirmPassword_lEdit);
    confirmPassword_hLay->addStretch();
    return confirmPassword_hLay;
}

void RegistrationWidget::slot_sign_pBtn_clicked()
{
    emit signal_changeSign(MainWidgets::Authorization);
}

void RegistrationWidget::slot_signUpRequest()
{
    if (login_lEdit->text().isEmpty()
            || password_lEdit->text().isEmpty()
            || confirmPassword_lEdit->text().isEmpty())
    {
        return;
    }
    if (password_lEdit->text() != confirmPassword_lEdit->text())
    {
        showError(QStringLiteral("Passwords don't match"));
        return;
    }

    _processor->signUp_request(login_lEdit->text(), password_lEdit->text());
}

void RegistrationWidget::slot_signUpResponse(const std::string &status)
{
    if (status == "ok")
    {
        emit signal_changeSign(MainWidgets::Chat);
    }
    else if (status == "login_exists")
    {
        showError(QStringLiteral("Login already exists"));
    }
    else if (status == "already_signed")
    {
        showError(QStringLiteral("User is already registered"));
    }
    else
    {
        showError(QStringLiteral("Error"));
    }
}
