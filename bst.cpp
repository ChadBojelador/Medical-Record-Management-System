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
    if (root == nullptr || root->key == key)
        return root;
    if (key < root->key)
        return searchBST(root->left, key);
    else
        return searchBST(root->right, key);
}
