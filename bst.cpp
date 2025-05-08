#include "bst.h"




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
