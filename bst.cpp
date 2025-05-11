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

BstNode* bst::deleteHelper(BstNode* node, const QString& key)
{
    if (!node) return node;

    if (key < node->id)
        node->left = deleteHelper(node->left, key);
    else if (key > node->id)
        node->right = deleteHelper(node->right, key);
    else {
        // Node with one or no child
        if (!node->left) {
            BstNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            BstNode* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children
        BstNode* temp = minValueNode(node->right);
        node->id = temp->id;
        // Copy all data fields
        node->fullName = temp->fullName;
        node->ageStr = temp->ageStr;
        // ... copy all other fields ...
        node->right = deleteHelper(node->right, temp->id);
    }
    return node;
}

BstNode* bst::minValueNode(BstNode* node)
{
    BstNode* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

void bst::deleteNode(const QString& key)
{
    root = deleteHelper(root, key);
}
QList<BstNode*> bst::getAllNodes() const {
    QList<BstNode*> nodes;
    inOrderTraversal(root, nodes);
    return nodes;
}

void bst::inOrderTraversal(BstNode* node, QList<BstNode*>& list) const {
    if (!node) return;
    inOrderTraversal(node->left, list);
    list.append(node);
    inOrderTraversal(node->right, list);
}
BstNode* bst::search(const QString& key) {
    return searchRecursive(root, key);
}

BstNode* bst::searchRecursive(BstNode* node, const QString& key) {
    if (node == nullptr || node->key == key)
        return node;
    if (key < node->key)
        return searchRecursive(node->left, key);
    return searchRecursive(node->right, key);
}
