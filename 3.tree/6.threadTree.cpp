/*************************************************************************
	> File Name: 6.threadTree.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  2/15 19:12:56 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NORMAL 0
#define THREAD 1


typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
    int ltag, rtag;
} Node;

Node *init_Node(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    p->ltag = p->rtag = NORMAL;
    return p;
}


Node *insert(Node *root, int val) {
    if (!root) {
        return init_Node(val);
    }
    if (root->data == val) return root;
    if (val < root->data) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    return root;
}

void in_order(Node *root) {
    if (!root) return ;
    if (root->ltag == NORMAL) in_order(root->lchild);
    printf("%d ", root->data);
    if (root->rtag == NORMAL) in_order(root->rchild);
    return ;
}


void clear_Node(Node *root) {
    if (!root) return;
    if (root->ltag == NORMAL) clear_Node(root->lchild);
    if (root->rtag == NORMAL) clear_Node(root->rchild);
    free(root);
    return;
}

void build_thread(Node *root) {
    if (!root) return ;
    static Node *pre = NULL;
    build_thread(root->lchild);
    if (!root->lchild) {
        root->lchild = pre;
        root->ltag = THREAD;
    }
    if (pre && pre->rchild == NULL) {
        pre->rchild = root;
        pre->rtag = THREAD;
    }
    pre = root;
    build_thread(root->rchild);
    return;
}

Node *most_left(Node *p) {
    while (p && p->ltag == NORMAL && p->lchild) p = p->lchild;
    return p;
}


void output(Node *root) {
    Node *p = most_left(root);
    while (p) {
        printf("%d ", p->data);
        if (p->rtag == THREAD) {
            p = p->rchild;
        } else {
            p = most_left(p->rchild);
        }
    }
    return ;
}

int main() {
    srand(time(0));
    #define MAX_OP 20
    Node *root = NULL;
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        root = insert(root, val);
    }
    build_thread(root);
    output(root), printf("\n");
    in_order(root), printf("\n");
    clear_Node(root);
    return 0;
}
