#include "TreeTask.h"
#include "structures/treeBalanced.h"

void treeTask() {
    TreeBalanced tree;
    tree.insert(22);
    tree.insert(28);
    tree.insert(11);
    tree.insert(12);
    tree.insert(47);
    tree.insert(34);
    tree.insert(30);
    tree.insert(0);
    tree.insert(13);
    tree.insert(26);
    tree.insert(27);
    tree.printTree();
    cout << "--------------" << endl;
    tree.insert(11); //only unic values
    tree.printTree();
    cout << "--------------" << endl;
    tree.del(28);
    tree.printTree();
    cout << "--------------" << endl;
}
