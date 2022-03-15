#include "MainWindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    std::locale::global(std::locale(""));
    ui->setupUi(this);
    connect(ui->send_pBtn, &QPushButton::clicked, this, &MainWindow::slot_sendMsg);

    _clientThread = std::make_unique<ClientThread>();
    connect(this, &MainWindow::signal_stopClient, _clientThread.get(), &ClientThread::slot_stopClient);
    connect(this, &MainWindow::signal_sendMsg, _clientThread.get(), &ClientThread::signal_sendMsgToThread);
    connect(_clientThread.get(), &ClientThread::signal_getMsgFromThread, this, &MainWindow::slot_getMsg);
    _clientThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    emit signal_stopClient();
    _clientThread->wait(100);
}

void MainWindow::slot_sendMsg()
{
    if (!ui->msg_lEdit->text().isEmpty())
    {
        emit signal_sendMsg(ui->msg_lEdit->text());
    }
}

void MainWindow::slot_getMsg(QString msg)
{
    if (msg.isEmpty())
    {
        return;
    }
    ui->textEdit->setText(ui->textEdit->toPlainText() + msg);
}
