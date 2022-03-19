#include "MainWindow.h"

#include "AuthorizationWidget.h"
#include "RegistrationWidget.h"
#include "ChatWidget.h"

#include <QStackedWidget>
#include <QDebug>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    std::locale::global(std::locale(""));
    qRegisterMetaType<MainWidgets>();


    auto processor = std::make_shared<ClientProcessor>();
    initUi(processor);
    processor->start();
}

void MainWindow::initUi(const std::shared_ptr<IClientProcessor> &msgProcessor)
{
    setMinimumSize(QSize(600, 400));
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    main_widget = new QStackedWidget(this);

    auto authorizationWidget = new AuthorizationWidget(msgProcessor, main_widget);
    authorizationWidget->init();
    connect(authorizationWidget, &AuthorizationWidget::signal_changeSign,
            this, &MainWindow::slot_changeWidget);
    main_widget->insertWidget(static_cast<int>(MainWidgets::Authorization), authorizationWidget);

    auto registrationWidget = new RegistrationWidget(msgProcessor, main_widget);
    registrationWidget->init();
    connect(registrationWidget, &RegistrationWidget::signal_changeSign,
            this, &MainWindow::slot_changeWidget);
    main_widget->insertWidget(static_cast<int>(MainWidgets::Registration), registrationWidget);

    auto chatWidget = new ChatWidget(msgProcessor, main_widget);
    connect(this, &MainWindow::signal_updateContactList, chatWidget, &ChatWidget::updateContactList);
    main_widget->insertWidget(static_cast<int>(MainWidgets::Chat), chatWidget);

    setCentralWidget(main_widget);
}

void MainWindow::slot_changeWidget(MainWidgets wgt)
{
    main_widget->setCurrentIndex(static_cast<int>(wgt));
    if (wgt == MainWidgets::Chat)
    {
        emit signal_updateContactList();
    }
}

