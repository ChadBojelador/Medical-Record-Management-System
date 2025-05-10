#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Make
    MainWindow w;
    w.show();
    return a.exec();
}
