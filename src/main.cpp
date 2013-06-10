#include <QtWidgets/QApplication>
#include <QTranslator>
#include <QLocale>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator appTranslator;
//    appTranslator.load("spreadsheet_" + QLocale::system().name(), ":");
    a.installTranslator(&appTranslator);
    MainWindow w;
    w.show();



    return a.exec();
}
