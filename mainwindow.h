#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bst.h>
#include <QtSql>
#include <QtCore>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonLogin_clicked();

    void on_lineEditID_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_list_clicked();

    void on_addpatient_clicked();

    void on_pushButton_clicked();

    void on_exit1_clicked();

    void on_searchTable_clicked();

    void on_pushbuttonEXIT_clicked();

    void on_refreshButton_clicked();

    void on_deleteButton_clicked();
   void on_checkBox_Sort_stateChanged(int arg1);


private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    BstNode* root = nullptr;
    bst tree;
    void clearTable();
    void reloadDatabase();
    void loadDatabaseIntoBST();
void showPatientData(const QString& patientID);
};
#endif // MAINWINDOW_H
