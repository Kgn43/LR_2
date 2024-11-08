#include "treeBalanced.h"

TreeNode* TreeNode::insert(const int data) {
    if (data < this->data) {
        if (this->left == nullptr) {
            this->left = new TreeNode(data);
        }
        else {
            this->left->insert(data);
        }
    }
    else if (data > this->data){
        if (this->right == nullptr) {
            this->right = new TreeNode(data);
        }
        else {
            this->right->insert(data);
        }
    }
    return this;
}

TreeNode* TreeNode::remove(const int data) {
    if (data < this->data) {
        if (this->left != nullptr) {
            this->left = this->left->remove(data);
        }
    }
    else if (data > this->data) {
        if (this->right != nullptr) {
            this->right = this->right->remove(data);
        }
    }
    else {
        if (this->left == nullptr && this->right == nullptr) { //no child nodes
            delete this;
            return nullptr;
        }
        if (this->left == nullptr) { //right child node exist
            TreeNode* temp = this->right;
            delete this;
            return temp;
        }
        if (this->right == nullptr) { //left child node exist
            TreeNode* temp = this->left;
            delete this;
            return temp;
        }
        TreeNode* minNode = this->right;
        while (minNode->left != nullptr) {
            minNode = minNode->left;
        }
        this->data = minNode->data;
        this->right = this->right->remove(minNode->data);
    }
    return this;
}

void TreeNode::print(const int level) const {
    if (this->right != nullptr) {
        this->right->print(level + 1);
    }
    std::cout << std::string(level * 4, ' ') << this->data << std::endl;
    if (this->left != nullptr) {
        this->left->print(level + 1);
    }
}

void TreeBalanced::insert(const int data) {
    if (this->root == nullptr) {
        this->root = new TreeNode(data);
    }
    else {
        this->root->insert(data);
    }
}

void TreeBalanced::del(const int data) {
    if (this->root != nullptr) {
        this->root = this->root->remove(data);
    }
}

void TreeBalanced::printTree() const {
    if (this->root != nullptr) {
        this->root->print();
    }
}
