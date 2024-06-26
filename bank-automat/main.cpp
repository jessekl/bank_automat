#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qss
    QFile styleFile("styles/style.qss");
    styleFile.open(QFile::ReadOnly );
    QString style(styleFile.readAll());
    a.setStyleSheet(style);
    MainWindow window;


    return a.exec();
}

