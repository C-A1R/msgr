#ifndef AUTHORIZATIONWIDGET_H
#define AUTHORIZATIONWIDGET_H

#include <QWidget>

#include "client_processor/ClientProcessor.h"
#include "MainWidgets.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QHBoxLayout;

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
    virtual QHBoxLayout *createConfirmLine() {return nullptr;}

protected:
    void setupUi();
    void showError(const QString &err);

signals:
    void signal_changeSign(MainWidgets);

private slots:
    virtual void slot_sign_pBtn_clicked();
    void slot_SignInRequest();
    void slot_SignInResponse(const std::string &status);
};

#endif // AUTHORIZATIONWIDGET_H
