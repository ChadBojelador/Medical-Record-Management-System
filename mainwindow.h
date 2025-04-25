#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
