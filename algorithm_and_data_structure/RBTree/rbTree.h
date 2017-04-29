/*************************************************************************
 > File Name: rbTree.h
 > Author: zhushh
 > Mail: 
 > Created Time: Fri 28 Apr 2017 07:45:10 PM CST
 ************************************************************************/

#ifndef _RBTREE_H
#define _RBTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef int KEY;
typedef enum { RED, BLACK } NODECOLOR;
typedef struct _Node {
    NODECOLOR color;
    KEY key;
    struct _Node* left;
    struct _Node* right;
    struct _Node* p;

    _Node(NODECOLOR c, KEY k) {
        this->color = c;
        this->key = k;
        this->left = this->right = this->p = NULL;
    }
} TNode;

typedef struct _Tree {
    TNode* root;
    TNode* nil;
    _Tree() {
        root = nil = new TNode(BLACK, 0);
    }
} RBTree;

RBTree* RBTreeCreator();
void RBTreeFree(RBTree* T);
void RBTreeFreeHelper(TNode* cur, TNode* nil);
void RBTreeTransplant(RBTree* T, TNode* u, TNode* v);
TNode* TreeMinimum(TNode* z, TNode* nil);
TNode* RBTreeSearch(RBTree* T, KEY key);

void LeftRotate(RBTree* T, TNode* x);
void RightRotate(RBTree* T, TNode* y);
void RBTreeInsert(RBTree* T, TNode* z);
void RBTreeInsertFixup(RBTree* T, TNode* z);
void RBTreeDelete(RBTree* T, TNode* z);
void RBTreeDeleteFixup(RBTree* T, TNode* x);

void RBTreePrint(RBTree* T);
#endif
