/*************************************************************************
	> File Name: 10.AVL.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年04月23日 星期四 18时17分35秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define H(root) (root)->h
#define L(root) (root)->lchild
#define R(root) (root)->rchild

#define K(root) (root)->key

typedef struct Node {
    int key, h;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = NIL->h = 0;
    NIL->lchild = NIL->rchild = NIL;
}


Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->h = 1;
    return p;
}

void update_height(Node *root) {
    root->h = H(L(root)) > H(R(root)) ? H(L(root)) : H(R(root));
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;

    update_height(root);
    update_height(temp);
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;

    update_height(root);
    update_height(temp);
    return temp;   
}


Node *maintain(Node *root) {
    if (abs(H(L(root) - H(R(root)))) <= 1) return root;//不用调整
    if (H(L(root)) > H(R(root))) {
        /*第一个字母肯定是Ｌ*/
        if (H(R(L(root))) > H(L(L(root)))) {
            /*第二个字母是R*/
            /*进行小左旋*/
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        /*第一个字母肯定是R*/
        if (H(L(R(root))) > H(R(R(root)))) {
            /*第二个字母是L*/
            /*进行小右旋*/
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    update_height(root);
    return maintain(root);
}

Node *predeccessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) {
        root->lchild = erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
            free(root);
            return temp;
        } else {
            Node *temp = predeccessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    update_height(root);
    return maintain(root);
}


void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}


void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d, %d, %d)\n", K(root), K(L(root)), K(R(root)));
    output(root->lchild);
    output(root->rchild);
    return ;
}


int main() {
    #define MAX_OP 20
    Node *root = NIL;
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        root = insert(root, val);

    }
    output(root);
    int val;
    while (~scanf("%d", &val)) {
        root = erase(root, val);
        printf("erase %d from AVL tree!\n", val);
        output(root);
    }
    return 0;
}
