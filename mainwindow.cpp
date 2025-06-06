#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bst.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QScrollArea>
#include <QScrollBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isEditing(false)
{
    ui->setupUi(this);

    ui->tableWidget->setSortingEnabled(true);

    ui->tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ui->tableWidget->resizeColumnsToContents();


    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableWidget->setColumnWidth(1, 400);
    ui->tableWidget->setColumnWidth(10, 300);
    ui->tableWidget->setColumnWidth(9, 300);
    ui->stackedWidget->setCurrentIndex(0);


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
    QSqlQuery query;
    if (!query.exec("SELECT ID, NAME, SUFFIX, AGE, BIRTHDATE, BLOOD_TYPE, CIVIL_STATUS, BIRTHPLACE, CONTACT_NO, RELIGION, NATIONALITY, ADDRESS, ROOM, TIME_ADMITTED, LEVEL_OF_CARE, DATE_ADMITTED, ADMIN_NAME, SEX FROM finaldb")) {
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }


    while (query.next()) {
        BstNode* node = new BstNode();
          node->key = node->id;
        node->id = query.value(0).toString();

        node->fullName = query.value(1).toString();

        node->suffix = query.value(2).toString();

        node->ageStr = query.value(3).toString();

        node->dateStr = query.value(4).toString();

        node->bloodType = query.value(5).toString();

        node->civilStatus = query.value(6).toString();

        node->birth = query.value(7).toString();

        node->contact = query.value(8).toString();

        node->religion = query.value(9).toString();

        node->nation = query.value(10).toString();

        node->address = query.value(11).toString();

        node->room = query.value(12).toString();

        node->time1 = query.value(13).toString();

        node->level = query.value(14).toString();

        node->dateAdmitted = query.value(15).toString();

        node->admin = query.value(16).toString();

        node->selectedGender = query.value(17).toString();


        tree.insert(node);

    }
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


    newNode->key = newNode->id;



    return newNode;
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
            QMessageBox::warning(this, "Welcome", "Logged in as Admin");
        }
        else{
            ui->lineEditID->clear();
            ui->lineEditID->setPlaceholderText("Incorrect admin ID");
            ui->lineEditID->setStyleSheet("border: 2px solid red;");
            QMessageBox::warning(this, "Login Failed", "Incorrect Admin ID!");
        }
    }

    else if (ui->radioPatient->isChecked()){
        QString enteredID = ui->lineEditID->text().trimmed();


        QList<BstNode*> results = tree.searchMultiple(enteredID);
        bool validPatient = false;

        foreach(BstNode* node, results) {
            if(node->id == enteredID) {
                validPatient = true;
                break;
            }
        }

        if(validPatient) {
            ui->stackedWidget->setCurrentIndex(3);  // Go to table view
            showPatientData(enteredID);
            QMessageBox::information(this, "Welcome", "Logged in as Patient.");
        }
        else {
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
    if (isEditing) {
        // Edit existing record
        BstNode* existingNode = tree.search(currentEditId);
        if (!existingNode) {
            QMessageBox::warning(this, "Error", "Record not found!");
            return;
        }


        existingNode->id = id;
        existingNode->surname = surname;
        existingNode->firstName = firstName;
        existingNode->middleName = middleName;
        existingNode->birth = birth;
        existingNode->religion = religion;
        existingNode->nation = nation;
        existingNode->room = room;
        existingNode->time1 = time1;
        existingNode->level = level;
        existingNode->admin = admin;
        existingNode->ageStr = ageStr;
        existingNode->dateAdmitted = dateAdmitted;
        existingNode->contact = contact;
        existingNode->address = address;
        existingNode->fullName = fullName;
        existingNode->suffix = suffix;
        existingNode->bloodType = bloodType;
        existingNode->civilStatus = civilStatus;
        existingNode->dateStr = dateStr;
        existingNode->selectedGender = selectedGender;

        QSqlQuery query;
        query.prepare("UPDATE finaldb SET ID=?, NAME=?, SUFFIX=?, AGE=?, BIRTHDATE=?, BLOOD_TYPE=?, CIVIL_STATUS=?, "
                      "BIRTHPLACE=?, CONTACT_NO=?, RELIGION=?, NATIONALITY=?, ADDRESS=?, ROOM=?, TIME_ADMITTED=?, "
                      "LEVEL_OF_CARE=?, DATE_ADMITTED=?, ADMIN_NAME=?, SEX=? WHERE ID=?");

        query.addBindValue(id);
        query.addBindValue(fullName);
        query.addBindValue(suffix);
        query.addBindValue(ageStr);
        query.addBindValue(dateStr);
        query.addBindValue(bloodType);
        query.addBindValue(civilStatus);
        query.addBindValue(birth);
        query.addBindValue(contact);
        query.addBindValue(religion);
        query.addBindValue(nation);
        query.addBindValue(address);
        query.addBindValue(room);
        query.addBindValue(time1);
        query.addBindValue(level);
        query.addBindValue(dateAdmitted);
        query.addBindValue(admin);
        query.addBindValue(selectedGender);
        query.addBindValue(currentEditId);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Record updated!");
            isEditing = false;
            currentEditId.clear();
            ui->lineEditID2->setReadOnly(false);
        } else {
            QMessageBox::critical(this, "Error", "Update failed: " + query.lastError().text());
        }
         } else {
    BstNode* newNode = CreateNodeFromUI(ui);
             if (tree.search(newNode->id)) {
                 QMessageBox::warning(this, "Error", "ID already exists!");
                 delete newNode;
                 return;
             }
    tree.insert(newNode);

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
        QMessageBox::information(this, "Success", "Record added successfully.");

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
          ui->lineEditContact->clear();
        ui->lineEditAddress->clear();
        return;
    } else {

        tree.deleteNode(newNode->id);
        delete newNode;
        QMessageBox::critical(this, "Error", "Insert failed: " + query.lastError().text());
    }
}

reloadDatabase();
if(ui->stackedWidget->currentIndex() == 3) {
    on_list_clicked();
}
}
void MainWindow::on_list_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    db.open();


    QSqlQuery query(db);
    query.prepare("SELECT * FROM finaldb ORDER BY NAME ASC");

    if (query.exec()) {
        ui->tableWidget->setRowCount(0);
        int row = 0;


        ui->tableWidget->setSortingEnabled(false);

        while (query.next()) {
            ui->tableWidget->insertRow(row);
            for (int col = 0; col < query.record().count(); ++col) {
                ui->tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
            }
            row++;
        }

        ui->tableWidget->setSortingEnabled(true);
        ui->tableWidget->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);
        ui->tableWidget->sortByColumn(1, Qt::AscendingOrder);
    } else {
        qDebug() << "Error retrieving data:" << query.lastError().text();
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
    QString searchTxt = ui->searchNameorID->text().trimmed();
    QList<BstNode*> results = tree.searchMultiple(searchTxt);

    ui->tableWidget->setRowCount(0);
    if (results.isEmpty()) {
        QMessageBox::information(this, "Not Found", "No matching records found.");
        return;
    }


    ui->tableWidget->setColumnCount(18);
    ui->tableWidget->setRowCount(results.size());

    for (int i = 0; i < results.size(); ++i) {
        BstNode* node = results[i];
        int col = 0;

        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->id));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->fullName));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->suffix));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->ageStr));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->dateStr));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->bloodType));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->civilStatus));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->birth));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->contact));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->religion));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->nation));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->address));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->room));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->time1));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->level));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->dateAdmitted));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->admin));
        ui->tableWidget->setItem(i, col++, new QTableWidgetItem(node->selectedGender));
    }
};

void MainWindow::on_pushbuttonEXIT_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::clearTable()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
}
void MainWindow::loadDatabaseIntoBST()
{
    QSqlQuery query;
    if (!query.exec("SELECT ID, NAME, SUFFIX, AGE, BIRTHDATE, BLOOD_TYPE, CIVIL_STATUS, BIRTHPLACE, CONTACT_NO, RELIGION, NATIONALITY, ADDRESS, ROOM, TIME_ADMITTED, LEVEL_OF_CARE, DATE_ADMITTED, ADMIN_NAME, SEX FROM finaldb")) {
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        BstNode* node = new BstNode();
        node->id = query.value(0).toString();
        node->key = node->id;
            node->id = query.value(0).toString();

            node->fullName = query.value(1).toString();

            node->suffix = query.value(2).toString();

            node->ageStr = query.value(3).toString();

            node->dateStr = query.value(4).toString();

            node->bloodType = query.value(5).toString();

            node->civilStatus = query.value(6).toString();

            node->birth = query.value(7).toString();

            node->contact = query.value(8).toString();

            node->religion = query.value(9).toString();

            node->nation = query.value(10).toString();

            node->address = query.value(11).toString();

            node->room = query.value(12).toString();

            node->time1 = query.value(13).toString();

            node->level = query.value(14).toString();

            node->dateAdmitted = query.value(15).toString();

            node->admin = query.value(16).toString();

            node->selectedGender = query.value(17).toString();

            tree.insert(node);
        }
    }

void MainWindow::reloadDatabase()
{
    tree.clear();
    loadDatabaseIntoBST();
};

void MainWindow::on_refreshButton_clicked()
{

    tree.clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);


    loadDatabaseIntoBST();


    if(ui->stackedWidget->currentIndex() == 3) {
        on_list_clicked();
    }

}

void MainWindow::on_deleteButton_clicked()
{

    QModelIndexList selected = ui->tableWidget->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a record to delete.");
        return;
    }


    int row = selected.first().row();
    QString id = ui->tableWidget->item(row, 0)->text();


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete",
                                  "Delete record for ID: " + id + "?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply != QMessageBox::Yes) return;


    QSqlQuery query;
    query.prepare("DELETE FROM finaldb WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error",
                              "Database deletion failed: " + query.lastError().text());
        return;
    }


    tree.deleteNode(id);


    if (ui->stackedWidget->currentIndex() == 3) {
        on_list_clicked();
    }

    QMessageBox::information(this, "Success", "Record deleted successfully.");
}


void MainWindow::showPatientData(const QString& patientID)
{

    QList<BstNode*> results = tree.searchMultiple(patientID);


    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(18);

    if(!results.isEmpty()) {

        BstNode* patientNode = nullptr;
        foreach(BstNode* node, results) {
            if(node->id == patientID) {
                patientNode = node;
                break;
            }
        }

        if(patientNode) {

            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableWidget->setRowCount(1);
            int col = 0;


            auto createReadOnlyItem = [](const QString& text) {
                QTableWidgetItem* item = new QTableWidgetItem(text);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                return item;
            };



            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->id));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->fullName));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->suffix));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->ageStr));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->dateStr));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->bloodType));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->civilStatus));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->birth));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->contact));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->religion));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->nation));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->address));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->room));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->time1));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->level));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->dateAdmitted));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->admin));
            ui->tableWidget->setItem(0, col++, new QTableWidgetItem(patientNode->selectedGender));
                   ui->tableWidget->setFocusPolicy(Qt::NoFocus);
        }
    }
}
void MainWindow::on_editButton_clicked()
{
    QModelIndexList selected = ui->tableWidget->selectionModel()->selectedRows(0);
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a record to edit.");
        return;
    }

    int row = selected.first().row();
    QString id = ui->tableWidget->item(row, 0)->text();

    BstNode* node = tree.search(id);
    if (!node) {
        QMessageBox::warning(this, "Error", "Patient record not found in system.");
        return;
    }


    ui->lineEditID2->setText(node->id);
    ui->lineEditSurname->setText(node->surname);
    ui->lineEditFirst->setText(node->firstName);
    ui->lineEditMI->setText(node->middleName);
    ui->lineEditbirth->setText(node->birth);
    ui->lineEditReligion->setText(node->religion);
    ui->lineEditNation->setText(node->nation);
    ui->lineEditRoom->setText(node->room);
    ui->lineEditTime1->setText(node->time1);
    ui->lineEditLevel->setText(node->level);
    ui->lineEditDate->setText(node->dateAdmitted);
    ui->lineEditAdmin->setText(node->admin);
    ui->lineEditContact->setText(node->contact);
    ui->lineEditAddress->setText(node->address);


    bool ageOk;
    int age = node->ageStr.toInt(&ageOk);
    if (ageOk) ui->age->setValue(age);

    if (node->selectedGender == "Male") {
        ui->radioMale->setChecked(true);
    } else if (node->selectedGender == "Female") {
        ui->radioFemale->setChecked(true);
    }


    ui->suffix->setCurrentText(node->suffix);
    ui->bloodType->setCurrentText(node->bloodType);
    ui->civilStatus->setCurrentText(node->civilStatus);

    QDate birthDate = QDate::fromString(node->dateStr, "yyyy-MM-dd");
    if (birthDate.isValid()) {
        ui->dateEdit->setDate(birthDate);
    }


    isEditing = true;
    currentEditId = id;
    ui->lineEditID2->setReadOnly(true);
    ui->stackedWidget->setCurrentIndex(1);


    QScrollArea* scrollArea = qobject_cast<QScrollArea*>(ui->stackedWidget->currentWidget());
    if (scrollArea && scrollArea->verticalScrollBar()) {
        scrollArea->verticalScrollBar()->setValue(0);
    }
}


    void MainWindow::onTableDoubleClicked(int row, int column)
    {
        Q_UNUSED(column);
        QString patientId = ui->tableWidget->item(row, 0)->text();
        showEditFormWithData(patientId);
    }
    void MainWindow::showEditFormWithData(const QString& patientId)
    {
        BstNode* node = tree.search(patientId);
        if (!node) return;


        ui->lineEditID2->setText(node->id);
        ui->lineEditSurname->setText(node->surname);
        ui->lineEditFirst->setText(node->firstName);
        ui->lineEditMI->setText(node->middleName);
        ui->lineEditbirth->setText(node->birth);
        ui->lineEditReligion->setText(node->religion);
        ui->lineEditNation->setText(node->nation);
        ui->lineEditRoom->setText(node->room);
        ui->lineEditTime1->setText(node->time1);
        ui->lineEditLevel->setText(node->level);
        ui->lineEditDate->setText(node->dateAdmitted);
        ui->lineEditAdmin->setText(node->admin);
        ui->lineEditContact->setText(node->contact);
        ui->lineEditAddress->setText(node->address);
        ui->age->setValue(node->ageStr.toInt());


        if (node->selectedGender == "Male") ui->radioMale->setChecked(true);
        else if (node->selectedGender == "Female") ui->radioFemale->setChecked(true);


        ui->suffix->setCurrentText(node->suffix);
        ui->bloodType->setCurrentText(node->bloodType);
        ui->civilStatus->setCurrentText(node->civilStatus);


        QDate birthDate = QDate::fromString(node->dateStr, "yyyy-MM-dd");
        ui->dateEdit->setDate(birthDate);


        ui->stackedWidget->setCurrentIndex(1);
        isEditing = true;
        currentEditId = patientId;
        ui->lineEditID2->setReadOnly(true);
    }

