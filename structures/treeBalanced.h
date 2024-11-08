#ifndef TREEBALANCED_H
#define TREEBALANCED_H

#include <iostream>

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(const int data) : data(data), left(nullptr), right(nullptr) {}

    TreeNode* insert(int data);
    TreeNode* remove(int data);
    void print(int level = 0) const;
};

class TreeBalanced {
    TreeNode *root;

public:
    TreeBalanced() : root(nullptr) {}

    void insert(int data);
    void del(int data);
    void printTree() const;

};




#endif //TREEBALANCED_H
