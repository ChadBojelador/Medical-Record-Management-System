#ifndef BST_H
#define BST_H

#include <QString>
#include <QList>

struct BstNode {
    QString key; // Used for BST ordering (ID)
    // Patient Data Fields
    QString id;
    QString surname;
    QString firstName;
    QString middleName;
    QString suffix;
    QString fullName;
    QString ageStr;
    QString dateStr;
    QString bloodType;
    QString civilStatus;
    QString birth;
    QString contact;
    QString religion;
    QString nation;
    QString address;
    QString room;
    QString time1;
    QString level;
    QString dateAdmitted;
    QString admin;
    QString selectedGender;

    BstNode* left;
    BstNode* right;

    BstNode() : left(nullptr), right(nullptr) {}
};

class bst
{
public:
    bst();
    ~bst();

    // Core BST operations
    void insert(BstNode* newNode);
    QList<BstNode*> searchMultiple(const QString& searchText) const;

    void clear();

private:
    BstNode* root;

    // Helper functions
    BstNode* insertHelper(BstNode* node, BstNode* newNode);
    void searchHelper(BstNode* node, const QString& searchText, QList<BstNode*>& results) const;
    void clearTree(BstNode* node);

};

#endif // BST_H
