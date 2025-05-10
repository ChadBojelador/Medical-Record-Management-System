#include "bst.h"
#include <QDebug>

bst::bst() : root(nullptr) {}

bst::~bst() {
    clearTree(root);
}

void bst::clearTree(BstNode* node) {
    if (node) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
}

BstNode* bst::insertHelper(BstNode* node, BstNode* newNode) {
    if (!node) return newNode;

    if (newNode->key < node->key)
        node->left = insertHelper(node->left, newNode);
    else
        node->right = insertHelper(node->right, newNode);

    return node;
}

void bst::insert(BstNode* newNode) {
    if (!newNode) return;
    newNode->key = newNode->id; // Ensure key is set before insertion
    root = insertHelper(root, newNode);
}

void bst::searchHelper(BstNode* node, const QString& searchText, QList<BstNode*>& results) const {
    if (!node) return;

    if (node->id.contains(searchText, Qt::CaseInsensitive) ||
        node->fullName.contains(searchText, Qt::CaseInsensitive)) {
        results.append(node);
    }

    searchHelper(node->left, searchText, results);
    searchHelper(node->right, searchText, results);
}

QList<BstNode*> bst::searchMultiple(const QString& searchText) const {
    QList<BstNode*> results;
    searchHelper(root, searchText, results);
    return results;
}
void bst::clear()
{
    clearTree(root);
    root = nullptr;
}

