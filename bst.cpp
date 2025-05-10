#include "bst.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


BstNode* Insert(BstNode* root, BstNode* newNode) {
    if (root == nullptr) {
        return newNode;
    }

    if (newNode->id < root->id) {
        root->left = Insert(root->left, newNode);
    } else {
        root->right = Insert(root->right, newNode);
    }

    return root;
}



bst::bst() {}


void bst::InsertNode(BstNode* newNode) {
    root = Insert(root, newNode);
}
BstNode* searchBST(BstNode* root, const QString& key) {
    if (root == nullptr)
        return nullptr;

    if (root->id.compare(key, Qt::CaseInsensitive) == 0 ||
        root->fullName.compare(key, Qt::CaseInsensitive) == 0) {
        return root;
    }

    // You can still use ID as a base for ordering in the tree,
    // but since search needs to compare both, you must search both subtrees.
    BstNode* leftResult = searchBST(root->left, key);
    if (leftResult != nullptr) return leftResult;

    return searchBST(root->right, key);
}
void searchBSTMultiple(BstNode* root, const QString& key, QList<BstNode*>& results) {
    if (root == nullptr) return;

    qDebug() << "Checking node:" << root->id << "|" << root->fullName;

    // Use contains() for partial case-insensitive matching
    if (root->id.contains(key, Qt::CaseInsensitive) ||
        root->fullName.contains(key, Qt::CaseInsensitive)) {
        qDebug() << "MATCH FOUND!";
        results.append(root);
    }

    // Recursive search in left and right subtrees
    searchBSTMultiple(root->left, key, results);
    searchBSTMultiple(root->right, key, results);
}


