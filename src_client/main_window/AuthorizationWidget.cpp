#include "AuthorizationWidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include <QDebug>

AuthorizationWidget::AuthorizationWidget(const std::shared_ptr<IMsgProcessor> &msgProcessor, QWidget *parent)
    : QWidget{parent}, _msgProcessor{msgProcessor}
{
}

void AuthorizationWidget::init()
{
    setupUi();
}

void AuthorizationWidget::setupUi()
{
    auto main_vLay = new QVBoxLayout();

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

void AuthorizationWidget::slot_sign_pBtn_clicked()
{
    emit signal_changeSign(MainWidgets::Registration);
}
