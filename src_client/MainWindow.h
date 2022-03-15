#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "client/ClientThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    std::unique_ptr<ClientThread> _clientThread;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signal_stopClient();
    void signal_sendMsg(QString msg);
private slots:
    void slot_sendMsg();
    void slot_getMsg(QString msg);
};
#endif // MAINWINDOW_H
