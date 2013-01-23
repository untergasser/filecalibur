#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QString hashDeep_Path = "\\bin\\";
    QString hashDeep_Executable = "hasdeep64.exe";

    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
