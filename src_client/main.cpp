#include <QApplication>

#include "main_window/MainWindow.h"

#include <string>

int main(int argc, char** argv)
{
    qRegisterMetaType<std::string>();

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
