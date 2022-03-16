#ifndef AUTHORIZATIONWIDGET_H
#define AUTHORIZATIONWIDGET_H

#include <QWidget>

#include "client_processor/ClientProcessor.h"
#include "MainWidgets.h"

class QLineEdit;
class QPushButton;
class QHBoxLayout;

class AuthorizationWidget : public QWidget
{
    Q_OBJECT

protected:
    QLineEdit *login_lEdit{nullptr};
    QLineEdit *password_lEdit{nullptr};
    QPushButton *sign_pBtn{nullptr};
    QPushButton *changeSign_pBtn{nullptr};

    std::shared_ptr<IClientProcessor> _processor;

public:
    explicit AuthorizationWidget(const std::shared_ptr<IClientProcessor> &processor, QWidget *parent = nullptr);
    virtual void init();

private:
    void setupUi();
    virtual QHBoxLayout *createConfirmLine() {return nullptr;}

signals:
    void signal_changeSign(MainWidgets);

private slots:
    virtual void slot_sign_pBtn_clicked();
};

#endif // AUTHORIZATIONWIDGET_H
