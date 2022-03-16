#include <QApplication>

#include "main_window/MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
