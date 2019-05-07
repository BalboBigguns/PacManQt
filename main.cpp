#include <QApplication>

#include "mainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    window.setFixedSize(800, 600); //SVGA
   
    MainWindow game(&window);

    window.show();
    return app.exec();
}