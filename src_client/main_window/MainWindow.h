#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "MainWidgets.h"

class QStackedWidget;
class IClientProcessor;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStackedWidget *main_widget{nullptr};

public:
    MainWindow(QWidget *parent = nullptr);

private:
    ///инициализация пользовательского интерфейса
    void initUi(const std::shared_ptr<IClientProcessor> &msgProcessor);

signals:
    void signal_updateContactList();

private slots:
    void slot_changeWidget(MainWidgets wgt);
};

Q_DECLARE_METATYPE(std::string)

#endif // MAINWINDOW_H
