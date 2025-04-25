#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->setColumnCount(2);
    QStringList headers;
    headers << "Name" << "ID" ;
    ui->tableWidget->setHorizontalHeaderLabels(headers);
     ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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


void MainWindow::on_pushButton_2_clicked()
{
    QString surname = ui->lineEditSurname->text();
    QString firstName = ui->lineEditFirst->text();
    QString middleName = ui->lineEditMI->text();

    QString fullName = surname + ", " + firstName + " " + middleName;

    QString id = ui->lineEditID2->text();

    if (surname.isEmpty() || firstName.isEmpty() || id.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);


    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(fullName));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(id));


    ui->lineEditSurname->clear();
    ui->lineEditFirst->clear();
    ui->lineEditMI->clear();
    ui->lineEditID2->clear();
}


void MainWindow::on_list_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_addpatient_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



