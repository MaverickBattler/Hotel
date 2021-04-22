#include "mainwindow.h"

#include <QApplication>
#include <QTextStream>
#include <QTextCodec>
#include <QTextStream>
int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
