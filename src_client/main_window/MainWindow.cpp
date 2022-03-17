#include "MainWindow.h"

#include "AuthorizationWidget.h"
#include "RegistrationWidget.h"
#include "ChatWidget.h"

#include <QStackedWidget>
#include <QDebug>
#include <QThread>

#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    std::locale::global(std::locale(""));
    qRegisterMetaType<MainWidgets>();
    qRegisterMetaType<std::string>();

    auto processor = std::make_shared<ClientProcessor>();
    setupUi(processor);
    while (!processor->_isStarted)
    {
        qDebug() << "connecting..." << processor->isRunning();
        processor->start();
        QThread::currentThread()->sleep(3);
    }
}

void MainWindow::setupUi(const std::shared_ptr<IClientProcessor> &msgProcessor)
{
    resize(600, 400);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(QSize(600, 400));

    main_widget = new QStackedWidget(this);

    auto authorizationWidget = new AuthorizationWidget(msgProcessor, main_widget);
    authorizationWidget->init();
    connect(authorizationWidget, &AuthorizationWidget::signal_changeSign,
            this, &MainWindow::slot_changeSign);
    main_widget->insertWidget(static_cast<int>(MainWidgets::Authorization), authorizationWidget);

    auto registrationWidget = new RegistrationWidget(msgProcessor, main_widget);
    registrationWidget->init();
    connect(registrationWidget, &RegistrationWidget::signal_changeSign,
            this, &MainWindow::slot_changeSign);
    main_widget->insertWidget(static_cast<int>(MainWidgets::Registration), registrationWidget);

    auto chatWidget = new ChatWidget(msgProcessor, main_widget);
    main_widget->insertWidget(static_cast<int>(MainWidgets::Chat), chatWidget);

    setCentralWidget(main_widget);
}

void MainWindow::slot_changeSign(MainWidgets wgt)
{
    main_widget->setCurrentIndex(static_cast<int>(wgt));
}

