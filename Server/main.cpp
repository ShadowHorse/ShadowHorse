#include <QApplication>
#include <QtCore>

#include <stdlib.h>

#include "gui/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    return app.exec();
}
