#include "AuthorizationWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include <QDebug>

AuthorizationWidget::AuthorizationWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent)
    : QWidget{parent}, _processor{processor}
{
}

void AuthorizationWidget::init()
{
    initUi();
    connect(sign_pBtn, &QPushButton::clicked, this, &AuthorizationWidget::slot_signInRequest);
    connect(_processor.get(), &IClientProcessor::signal_signInResponse, this, &AuthorizationWidget::slot_signInResponse);
}

void AuthorizationWidget::initUi()
{
    auto main_vLay = new QVBoxLayout();

    err_lbl = new QLabel(this);
    err_lbl->setStyleSheet(QStringLiteral("color: red;"));
    err_lbl->setVisible(false);
    auto err_hLay = new QHBoxLayout();
    err_hLay->addStretch();
    err_hLay->addWidget(err_lbl);
    err_hLay->addStretch();

    login_lEdit = new QLineEdit(this);
    login_lEdit->setPlaceholderText(QStringLiteral("Login"));
    auto login_hLay = new QHBoxLayout();
    login_hLay->addStretch();
    login_hLay->addWidget(login_lEdit);
    login_hLay->addStretch();

    password_lEdit = new QLineEdit(this);
    password_lEdit->setPlaceholderText(QStringLiteral("Password"));
    password_lEdit->setEchoMode(QLineEdit::Password);
    auto password_hLay = new QHBoxLayout();
    password_hLay->addStretch();
    password_hLay->addWidget(password_lEdit);
    password_hLay->addStretch();

    auto confirmPassword_hLay = createConfirmLine();

    sign_pBtn = new QPushButton(QStringLiteral("Sign in"), this);
    auto sign_hLay = new QHBoxLayout();
    sign_hLay->addStretch();
    sign_hLay->addWidget(sign_pBtn);
    sign_hLay->addStretch();

    changeSign_pBtn = new QPushButton(QStringLiteral("Create new account"), this);
    changeSign_pBtn->setFlat(true);
    changeSign_pBtn->setStyleSheet(QStringLiteral("QPushButton:flat{border: none; color: blue; font-size: 12px;}"));
    connect(changeSign_pBtn, &QPushButton::clicked, this, &AuthorizationWidget::slot_sign_pBtn_clicked);
    auto changeSign_hLay = new QHBoxLayout();
    changeSign_hLay->addStretch();
    changeSign_hLay->addWidget(changeSign_pBtn);
    changeSign_hLay->addStretch();

    main_vLay->addStretch();
    main_vLay->addLayout(err_hLay);
    main_vLay->addLayout(login_hLay);
    main_vLay->addLayout(password_hLay);
    if (confirmPassword_hLay)
    {
        main_vLay->addLayout(confirmPassword_hLay);
    }
    main_vLay->addLayout(sign_hLay);
    main_vLay->addLayout(changeSign_hLay);
    main_vLay->addStretch();

    setLayout(main_vLay);
}

void AuthorizationWidget::showError(const QString &err)
{
    err_lbl->setText(err);
    err_lbl->setVisible(true);
}

void AuthorizationWidget::slot_sign_pBtn_clicked()
{
    emit signal_changeSign(MainWidgets::Registration);
}

void AuthorizationWidget::slot_signInRequest()
{
    if (login_lEdit->text().isEmpty() || password_lEdit->text().isEmpty())
    {
        return;
    }
    _processor->signIn_request(login_lEdit->text(), password_lEdit->text());
}

void AuthorizationWidget::slot_signInResponse(const std::string &status)
{
    if (status == "ok")
    {
        emit signal_changeSign(MainWidgets::Chat);
    }
    else if (status == "login_not_exists")
    {
        showError(QStringLiteral("Login does not exist"));
    }
    else if (status == "password_incorrect")
    {
        showError(QStringLiteral("Password is incorrect"));
    }
    else if (status == "already_signed")
    {
        showError(QStringLiteral("User is already logged in"));
    }
    else
    {
        showError(QStringLiteral("Error"));
    }
}
