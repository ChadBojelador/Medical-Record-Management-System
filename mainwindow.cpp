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

    // 2. Execute SQL SELECT
    QSqlQuery query;
    if (!query.exec("SELECT ID, NAME, SUFFIX, AGE, BIRTHDATE, BLOOD_TYPE, CIVIL_STATUS, BIRTHPLACE, CONTACT_NO, RELIGION, NATIONALITY, ADDRESS, ROOM, TIME_ADMITTED, LEVEL_OF_CARE, DATE_ADMITTED, ADMIN_NAME, SEX FROM finaldb")) {
        qDebug() << "Query error:" << query.lastError().text();
        return;
    }

    // 3. Fetch rows and insert into BST
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

    // Populate fields from UI
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

    // CORRECTED: Set the BST key once (should be ID for proper BST ordering)
    newNode->key = newNode->id;  // This is the only key assignment needed

    // Remove all other key assignments - they're redundant and incorrect
    // The BST only needs one key value for node comparison

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

        // Search BST for patient ID
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

    BstNode* newNode = CreateNodeFromUI(ui);
    tree.insert(newNode); // Insert using bst method

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
*/
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
    QString searchTxt = ui->searchNameorID->text().trimmed();
    QList<BstNode*> results = tree.searchMultiple(searchTxt);

    ui->tableWidget->setRowCount(0);
    if (results.isEmpty()) {
        QMessageBox::information(this, "Not Found", "No matching records found.");
        return;
    }

    // Set column count to match your data fields (18 columns)
    ui->tableWidget->setColumnCount(18);
    ui->tableWidget->setRowCount(results.size());

    for (int i = 0; i < results.size(); ++i) {
        BstNode* node = results[i];
        int col = 0;  // Initialize column counter for each row

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
    tree.clear();  // Use your actual member name
    loadDatabaseIntoBST();
};

void MainWindow::on_refreshButton_clicked()
{
    // Clear existing data
    tree.clear();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // Reload from database
    loadDatabaseIntoBST();

    // Refresh the table view if we're on the list page
    if(ui->stackedWidget->currentIndex() == 3) {  // Assuming 3 is your table page index
        on_list_clicked();
    }

}

void MainWindow::on_deleteButton_clicked()
{
    // Get selected row
    QModelIndexList selected = ui->tableWidget->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select a record to delete.");
        return;
    }

    // Get ID from first column of selected row
    int row = selected.first().row();
    QString id = ui->tableWidget->item(row, 0)->text();

    // Confirm deletion
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete",
                                  "Delete record for ID: " + id + "?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply != QMessageBox::Yes) return;

    // Delete from database
    QSqlQuery query;
    query.prepare("DELETE FROM finaldb WHERE ID = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error",
                              "Database deletion failed: " + query.lastError().text());
        return;
    }

    // Delete from BST
    tree.deleteNode(id);  // Implement this in BST class

    // Refresh UI
    if (ui->stackedWidget->currentIndex() == 3) {  // If on table view
        on_list_clicked();  // Refresh table
    }

    QMessageBox::information(this, "Success", "Record deleted successfully.");
}

void MainWindow::on_checkBox_Sort_stateChanged(int state)
{
    Q_UNUSED(state);
    on_list_clicked(); // Refresh the table view with new sorting
}

void MainWindow::showPatientData(const QString& patientID)
{
    // Search for the specific patient
    QList<BstNode*> results = tree.searchMultiple(patientID);

    // Clear and prepare table
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(18);

    if(!results.isEmpty()) {
        // Find exact match
        BstNode* patientNode = nullptr;
        foreach(BstNode* node, results) {
            if(node->id == patientID) {
                patientNode = node;
                break;
            }
        }

        if(patientNode) {
            // Make table read-only
            ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tableWidget->setRowCount(1);
            int col = 0;

            // Create non-editable items
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

