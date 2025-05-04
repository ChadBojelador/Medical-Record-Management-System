#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() <<QSqlDatabase::drivers();

    ui->stackedWidget->setCurrentIndex(0);
    ui->tableWidget->setColumnCount(10);
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
    QString birth = ui->lineEditbirth->text();
    QString religion = ui->lineEditReligion->text();
    QString nation = ui->lineEditNation->text();
    QString room = ui->lineEditRoom->text();
    QString time1 = ui->lineEditTime1->text();
    QString level = ui->lineEditLevel->text();
    QString date = ui->lineEditDate->text();
    QString admin = ui->lineEditAdmin->text();



    QString fullName = surname + ", " + firstName + " " + middleName;

    QString id = ui->lineEditID2->text();

    if (surname.isEmpty() || firstName.isEmpty() || id.isEmpty()||birth.isEmpty() || religion.isEmpty() || nation.isEmpty()||
        room.isEmpty() || time1.isEmpty() || level.isEmpty()||date.isEmpty() || admin.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);


    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(fullName));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(id));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(room));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(time1));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(level));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(date));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(admin));
    ui->tableWidget->setItem(row, 7, new QTableWidgetItem(birth));
    ui->tableWidget->setItem(row, 8, new QTableWidgetItem(nation));
    ui->tableWidget->setItem(row, 9, new QTableWidgetItem(religion));

    ui->lineEditSurname->clear();
    ui->lineEditFirst->clear();
    ui->lineEditMI->clear();
    ui->lineEditID2->clear();
    ui->lineEditbirth->clear();
    ui->lineEditReligion->clear();
    ui->lineEditNation->clear();
    ui->lineEditRoom->clear();
    ui->lineEditTime1->clear();
    ui->lineEditLevel->clear();
    ui->lineEditDate->clear();
    ui->lineEditAdmin->clear();
}


void MainWindow::on_list_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_addpatient_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}






void MainWindow::on_exit1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

