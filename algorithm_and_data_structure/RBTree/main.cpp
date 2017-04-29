#include <iostream>
#include <vector>
using namespace std;

#include "rbTree.h"

int main() {
    RBTree* t = RBTreeCreator();
    int data[] = {5, 11, 2, 48, 13, 6, 22, 1, 50, 100, 64};
    for (int i = 0; i < 11; i++) {
        cout<< "insert: " << data[i] << endl;
        RBTreeInsert(t, new TNode(RED, data[i]) );
    }
    cout << "Print:" << endl;
    RBTreePrint(t);

    int v[] = {6, 5, 11, 20, 44, 50};
    TNode* ptr = NULL;
    for (int i = 0; i < 6; i++) {
        cout << "search key = " << v[i] << ", result = ";
        if ((ptr = RBTreeSearch(t, v[i])) != t->nil) {
            cout << "True";
        } else {
            cout << "False";
        }
        cout << endl;
    }

    int val;
    for (int i = 0; i < 3; i++) {
        cout << "Input delete value: ";
        cin >> val;
        if ((ptr = RBTreeSearch(t, val)) != t->nil) {
            RBTreeDelete(t, ptr);
            RBTreePrint(t);
        }
    }
    RBTreeFree(t);
    return 0;
}
