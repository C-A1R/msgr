#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>

#include <QMainWindow>

#include "MainWidgets.h"

class QStackedWidget;
class IMsgProcessor;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QStackedWidget *main_widget{nullptr};

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void setupUi(const std::shared_ptr<IMsgProcessor> &msgProcessor);

private slots:
    void slot_changeSign(MainWidgets wgt);
};
#endif // MAINWINDOW_H
