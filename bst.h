#ifndef BST_H
#define BST_H
#include <QString>
#include "ui_mainwindow.h"

struct BstNode{
    QString id;
    QString surname;
    QString firstName;
    QString middleName;
    QString birth;
    QString religion;
    QString nation;
    QString room;
    QString time1;
    QString level;
    QString admin;
    QString ageStr;
    QString dateAdmitted;
    QString contact;
    QString address;
    QString selectedGender;
    QString fullName;
    QString suffix;
    QString bloodType;
    QString civilStatus;
    QString dateStr;

    QString key;
    QVariantMap data; // For example: {"ID": "1", "Name": "Juan"}
    BstNode* left;
    BstNode* right;
};

class bst
{


private:
    Ui::MainWindow *ui;
    BstNode* root = nullptr; // Declare it here


public:
    bst();

    BstNode* GetNewNode (const QString& id, const QString& surname, const QString& firstName, const QString& middleName,
                        const QString& birth, const QString& religion, const QString& nation, const QString& room,
                        const QString& time1, const QString& level, const QString& admin, const QString& ageStr,
                        const QString& dateAdmitted, const QString& contact, const QString& address, const QString& selectedGender,
                        const QString& fullName, const QString& suffix,const QString& bloodType,const QString& civilStatus,
                        const QString& dateStr);
    void InsertNode(BstNode* newNode);

};
BstNode* Insert(BstNode* root, BstNode* newNode);
BstNode* searchBST(BstNode* root, const QString& key);


#endif // BST_H
