#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include "mainwindow.h"

void connectToDatabase(); // Forward declaration
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connectToDatabase(); // Make
    MainWindow w;
    w.show();
    return a.exec();
}
