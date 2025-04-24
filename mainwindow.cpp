#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonLogin_clicked()
{
    if (ui->radioAdmin->isChecked()){
        QString enteredID = ui->lineEditID->text();

        if (enteredID =="admin123"){
            ui->stackedWidget->setCurrentIndex(1);
            QMessageBox::warning(this, "Welcome", "Logged in as Patient");
        }
        else{
            ui->lineEditID->clear();
            ui->lineEditID->setPlaceholderText("Incorrect admin ID");
            ui->lineEditID->setStyleSheet("border: 2px solid red;");
            QMessageBox::warning(this, "Login Failed", "Incorrect Admin ID!");
        }
    }

    else if (ui->radioPatient->isChecked()){
        QString enteredID = ui->lineEditID->text();

        if(enteredID == "PT-108863"){
            ui->stackedWidget->setCurrentIndex(2);
            QMessageBox::information(this, "Welcome", "Logged in as Patient.");
        }
        else{
            ui->lineEditID->clear();
            ui->lineEditID->setPlaceholderText("Incorrect Patient ID");
            ui->lineEditID->setStyleSheet("border: 2px solid red;");
            QMessageBox::warning(this, "Login Failed", "Incorrect Patient ID!");
        }
    }


}


void MainWindow::on_lineEditID_textChanged(const QString &text)
{
    Q_UNUSED(text);
    ui->lineEditID->setStyleSheet("");
}

