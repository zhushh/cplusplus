/*************************************************************************
 > File Name: rbTree.cpp
 > Author: zhushh
 > Mail: 
 > Created Time: Fri 28 Apr 2017 07:45:17 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

#include "rbTree.h"

RBTree* RBTreeCreator() {
    return new RBTree();
}

void RBTreeFreeHelper(TNode* cur, TNode* nil) {
    if (cur == nil) return;
    RBTreeFreeHelper(cur->left, nil);
    RBTreeFreeHelper(cur->right, nil);
    free(cur);
}

void RBTreeFree(RBTree* T) {
    RBTreeFreeHelper(T->root, T->nil);
    free(T->nil);
    free(T);
}

void LeftRotate(RBTree* T, TNode* x) {
    TNode* y = x->right;
    x->right = y->left;
    if (y->left != T->nil) {
        y->left->p = x->right;
    }

    y->p = x->p;
    if (x->p == T->nil) {
        T->root = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }

    y->left = x;
    x->p = y;
}

void RightRotate(RBTree* T, TNode* y) {
    TNode* x = y->left;
    y->left = x->right;
    if (x->right != T->nil) {
        x->right->p = y;
    }

    x->p = y->p;
    if (y->p == T->nil) {
        T->root = x;
    } else if (y == y->p->left) {
        y->p->left = x;
    } else {
        y->p->right = x;
    }

    x->right = y;
    y->p = x;
}

void RBTreeInsert(RBTree* T, TNode* z) {
    TNode* x = T->root;
    TNode* y = T->nil;

    while (x != T->nil) {
        y = x;
        if (x->key < z->key) {
            x = x->right;
        } else {
            x = x->left;
        }
    }

    z->color = RED;
    if (y == T->nil) {
        T->root = z;
    } else if (y->key < z->key) {
        y->right = z;
    } else {
        y->left = z;
    }
    z->p = y;
    z->left = z->right = T->nil;
    RBTreeInsertFixup(T, z);
}

void RBTreeInsertFixup(RBTree* T, TNode* z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            TNode* y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else if (z == z->p->right) {
                z = z->p;
                LeftRotate(T, z);
            } else {
                z->p->color = BLACK;
                z->p->p->color = RED;
                RightRotate(T, z->p->p);
            }
        } else {
            TNode* y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else if (z == z->p->left) {
                z = z->p;
                RightRotate(T, z);
            } else {
                z->p->color = BLACK;
                z->p->p->color = RED;
                LeftRotate(T, z->p->p);
            }
        }
    }
    T->root->color = BLACK;
}

void RBTreeTransplant(RBTree* T, TNode* u, TNode* v) {
    if (u->p == T->nil) {
        T->root = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else {
        u->p->right = v;
    }
    v->p = u->p;
}

TNode* TreeMinimum(TNode* z, TNode* nil) {
    TNode* cur = z;
    while (cur->left != nil) {
        cur = cur->left;
    }
    return cur;
}

TNode* RBTreeSearchHelper(TNode* root, TNode* nil, KEY key) {
    TNode* cur = root;
    if (cur == nil || cur->key == key) return cur;
    else if (cur->key > key) {
        return RBTreeSearchHelper(cur->left, nil, key);
    } else {
        return RBTreeSearchHelper(cur->right, nil, key);
    }
}

TNode* RBTreeSearch(RBTree* T, KEY key) {
    return RBTreeSearchHelper(T->root, T->nil, key);
}

void RBTreeDeleteFixup(RBTree* T, TNode* x) {
    while (x != T->root && x->color == BLACK) {
        if (x == x->p->left) {
            TNode* w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                LeftRotate(T, x->p);
                w = x->p->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->p;
            } else if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                RightRotate(T, w);
                w = x->p->right;
            } else {
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(T, x->p);
                x = T->root;
            }
        } else {
            TNode* w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                RightRotate(T, x->p);
                w = x->p->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->p;
            } else if (w->left->color == BLACK) {
                w->right->color = BLACK;
                w->color = RED;
                LeftRotate(T, w);
                w = x->p->left;
            } else {
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                RightRotate(T, x->p);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

void RBTreeDelete(RBTree* T, TNode* z) {
    TNode* x = T->nil;
    TNode* y = z;
    NODECOLOR yColor = y->color;
    if (z->left == T->nil) {
        x = z->right;
        RBTreeTransplant(T, z, z->right);
    } else if (z->right == T->nil) {
        x = z->left;
        RBTreeTransplant(T, z, z->left);
    } else {
        y = TreeMinimum(z->right, T->nil);
        yColor = y->color;
        x = y->right;
        if (y->p == z) {
            x->p = y;
        } else {
            RBTreeTransplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        RBTreeTransplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    if (yColor == BLACK) {
        RBTreeDeleteFixup(T, x);
    }
}

void printTNode(TNode* cur, TNode* nil) {
    if (cur == nil) return;
    cout << cur->key << ", ";
    if (cur->color == RED) {
        cout << "red";
    } else {
        cout << "black";
    }
    cout << endl;
    printTNode(cur->left, nil);
    printTNode(cur->right, nil);
}

void RBTreePrint(RBTree* T) {
    printTNode(T->root, T->nil);
}
