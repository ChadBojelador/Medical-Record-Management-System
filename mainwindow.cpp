#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bst.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);




    ui->tableWidget->resizeColumnsToContents();


    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableWidget->setColumnWidth(1, 400);
    ui->tableWidget->setColumnWidth(10, 300);
    ui->tableWidget->setColumnWidth(9, 300);
    ui->stackedWidget->setCurrentIndex(0);
}
BstNode* CreateNodeFromUI(Ui::MainWindow* ui) {
    BstNode* newNode = new BstNode();

    newNode->id = ui->lineEditID2->text();
    newNode->surname = ui->lineEditSurname->text();
    newNode->firstName = ui->lineEditFirst->text();
    newNode->middleName = ui->lineEditMI->text();
    newNode->birth = ui->lineEditbirth->text();
    newNode->religion = ui->lineEditReligion->text();
    newNode->nation = ui->lineEditNation->text();
    newNode->room = ui->lineEditRoom->text();
    newNode->time1 = ui->lineEditTime1->text();
    newNode->level = ui->lineEditLevel->text();
    newNode->admin = ui->lineEditAdmin->text();
    newNode->ageStr = QString::number(ui->age->value());
    newNode->dateAdmitted = ui->lineEditDate->text();
    newNode->contact = ui->lineEditContact->text();
    newNode->address = ui->lineEditAddress->text();

    if (ui->radioMale->isChecked()) {
        newNode->selectedGender = "Male";
    } else if (ui->radioFemale->isChecked()) {
        newNode->selectedGender = "Female";
    }

    newNode->fullName = newNode->surname + ", " + newNode->firstName + " " + newNode->middleName;
    newNode->suffix = ui->suffix->currentText();
    newNode->bloodType = ui->bloodType->currentText();
    newNode->civilStatus = ui->civilStatus->currentText();
    QDate birthday = ui->dateEdit->date();
    newNode->dateStr = birthday.toString("yyyy-MM-dd");

    newNode->left = nullptr;
    newNode->right = nullptr;

    return newNode;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void connectToDatabase() {

     QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("finaldb");
    db.setUserName("root");
    db.setPassword("");


    if (!db.open()) {
        QMessageBox::critical(nullptr, "Connection Failed", db.lastError().text());
    } else {
        QMessageBox::information(nullptr, "Success", "Connected to MySQL database!");
    }

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
        QString id = ui->lineEditID2->text();
        QString surname = ui->lineEditSurname->text();
        QString firstName = ui->lineEditFirst->text();
        QString middleName = ui->lineEditMI->text();
        QString birth = ui->lineEditbirth->text();
        QString religion = ui->lineEditReligion->text();
        QString nation = ui->lineEditNation->text();
        QString room = ui->lineEditRoom->text();
        QString time1 = ui->lineEditTime1->text();
        QString level = ui->lineEditLevel->text();
        QString admin = ui->lineEditAdmin->text();
        int ageValue = ui->age->value();
        QString ageStr = QString::number(ageValue);
        QString dateAdmitted = ui->lineEditDate->text();
        QString contact = ui->lineEditContact->text();
        QString address = ui->lineEditAddress->text();
        QString selectedGender;

        if (ui->radioMale->isChecked()) {
            selectedGender = "Male";
        } else if (ui->radioFemale->isChecked()) {
            selectedGender = "Female";
        }

        QString fullName = surname + ", " + firstName + " " + middleName;
        QString suffix = ui->suffix->currentText();
        QString bloodType = ui->bloodType->currentText();
        QString civilStatus = ui->civilStatus->currentText();
        QDate birthday = ui->dateEdit->date();
        QString dateStr = birthday.toString("yyyy-MM-dd");

        if (surname.isEmpty() || firstName.isEmpty() || id.isEmpty()||birth.isEmpty() || religion.isEmpty() || nation.isEmpty()||
            room.isEmpty() || time1.isEmpty() || level.isEmpty()||dateAdmitted.isEmpty() || admin.isEmpty() || contact.isEmpty()||address.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
            return;
        }
        else if (!ui->radioMale->isChecked() && !ui->radioFemale->isChecked()) {
            QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
            return;
        }
        else if (!ui->consent1->isChecked() && !ui->consent2->isChecked()) {
            QMessageBox::warning(this, "Consent Form", "Please read and check in all consent.");
            return;
        }
        else if (ageValue <= 0) {
            QMessageBox::warning(this, "Input Error", "Please enter a valid age.");
            return;
        }

        BstNode* newNode = CreateNodeFromUI(ui);
        if (!newNode) {
            QMessageBox::warning(this, "Error", "Failed to create BST node.");
            return;
        }

        root = Insert(root, newNode);

        QSqlQuery query;
        query.prepare("INSERT INTO finaldb (ID, NAME, SUFFIX, AGE, BIRTHDATE, BLOOD_TYPE, CIVIL_STATUS, BIRTHPLACE, CONTACT_NO, RELIGION, NATIONALITY, ADDRESS, ROOM, TIME_ADMITTED, LEVEL_OF_CARE, DATE_ADMITTED, ADMIN_NAME, SEX) "
                      "VALUES (:id, :fullName, :suffix, :age, :birthdate, :bloodType, :civilStatus, :birthplace, :contact, :religion, :nation, :address, :room, :time1, :level, :dateAdmitted, :admin, :gender)");

        query.bindValue(":id", id);
        query.bindValue(":fullName", fullName);
        query.bindValue(":suffix", suffix);
        query.bindValue(":age", ageStr);
        query.bindValue(":birthdate", dateStr);
        query.bindValue(":bloodType", bloodType);
        query.bindValue(":civilStatus", civilStatus);
        query.bindValue(":birthplace", birth);
        query.bindValue(":contact", contact);
        query.bindValue(":religion", religion);
        query.bindValue(":nation", nation);
        query.bindValue(":address", address);
        query.bindValue(":room", room);
        query.bindValue(":time1", time1);
        query.bindValue(":level", level);
        query.bindValue(":dateAdmitted", dateAdmitted);
        query.bindValue(":admin", admin);
        query.bindValue(":gender", selectedGender);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Student record added successfully.");
            return; // ✅ Suggestion 1: stop after success
        } else {
            QMessageBox::warning(this, "Error", "Failed to add record: " + query.lastError().text());
        }


    /*
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
}*/
}
void MainWindow::on_list_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    db.open();

    // Prepare and execute the query to fetch data
    QSqlQuery query(db);
    query.prepare("SELECT * FROM finaldb");

    if (query.exec()) {
        int row = 0;

        // Set the number of rows and columns in the table
        ui->tableWidget->setRowCount(query.size()); // Set number of rows
        ui->tableWidget->setColumnCount(query.record().count()); // Set number of columns

        // Iterate through the results and populate the table
        while (query.next()) {
            for (int col = 0; col < query.record().count(); ++col) {
                ui->tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
            }
            row++; // Increment row after inserting data
        }
    } else {
        qDebug() << "Error retrieving data: " << query.lastError().text();
    }

    db.close();
}


void MainWindow::on_addpatient_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}






void MainWindow::on_exit1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_searchTable_clicked()
{
    QString searchTxt = ui->searchNameorID->text();  // Assuming it's a QLineEdit
    if (searchTxt.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a name or ID to search.");
        return;
    }

    // Open the database
    db.open();

    QSqlQuery query(db);
    query.prepare("SELECT * FROM finaldb WHERE ID LIKE :searchText OR NAME LIKE :searchText");
    query.bindValue(":searchText", "%" + searchTxt + "%");

    // Execute the query and populate the table
    if (query.exec()) {
        int row = 0;

        // Set the number of rows and columns in the table
        ui->tableWidget->setRowCount(query.size()); // Set number of rows based on search results
        ui->tableWidget->setColumnCount(query.record().count()); // Set number of columns

        // Iterate through the results and populate the table
        while (query.next()) {
            for (int col = 0; col < query.record().count(); ++col) {
                ui->tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
            }
            row++; // Increment row after inserting data
        }
    } else {
        qDebug() << "Error retrieving data: " << query.lastError().text();
    }

    // Close the database
    db.close();
}



void MainWindow::on_pushbuttonEXIT_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



