/*************************************************************************
	> File Name: 2.tree.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月19日 星期二 23时30分43秒
 ************************************************************************/

//1h 2019.11.20 最大bug:insert_Node里面递归时忘了root->lchild = xxx和root->rchild = xxx;
//20min 2019.11.20
//23min 2019.11.22
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

typedef struct BinaryTree {
    Node *root;
    int n;
} BinaryTree;

Node *init_Node(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->lchild = node->rchild = NULL;
    return node;
}

BinaryTree *init_BinaryTree() {
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

void clear_Node(Node *root) {
    if (!root) return;
    clear_Node(root->lchild);
    clear_Node(root->rchild);
    free(root);
    return;
}

void clear_BinaryTree(BinaryTree *tree) {
    if (!tree) return;
    clear_Node(tree->root);
    free(tree);
    return;
}

Node *insert_Node(Node *root, int val, int *flag) {
    if (!root) {
        *flag = 1;
        return init_Node(val);
    }
    if (root->data == val) return root;
    if (val < root->data) root->lchild = insert_Node(root->lchild, val, flag);
    else root->rchild = insert_Node(root->rchild, val, flag);
    return root;
}

void insert_BinaryTree(BinaryTree *tree, int val) {
    if (!tree) return;
    int flag = 0;
    tree->root = insert_Node(tree->root, val, &flag);
    tree->n += flag;
    return;
}

void output_Node(Node *root) {
    if (!root) return;
    printf("%d(", root->data);
    output_Node(root->lchild);
    printf(",");
    output_Node(root->rchild);
    printf(")");
    return;
}

void output_BinaryTree(BinaryTree *tree) {
    if (!tree) return;
    printf("BinaryTree(%d) = ", tree->n);
    output_Node(tree->root);
    printf("\n");
    return;
}

void in_order_Node(Node *root) {
    if (!root) return;
    in_order_Node(root->lchild);
    printf("%d ", root->data);
    in_order_Node(root->rchild);
    return;
}

void in_order(BinaryTree *tree) {
    printf("in_order(%d) = ", tree->n);
    in_order_Node(tree->root);
    printf("\n");
    return;
}

void pre_order_Node(Node *root) {
    if (!root) return;
    printf("%d ", root->data);
    pre_order_Node(root->lchild);
    pre_order_Node(root->rchild);
    return;
}

void pre_order(BinaryTree *tree) {
    printf("pre_order(%d) = ", tree->n);
    pre_order_Node(tree->root);
    printf("\n");
    return;
}


void post_order_Node(Node *root) {
    if (!root) return;
    post_order_Node(root->lchild);
    post_order_Node(root->rchild);
    printf("%d ", root->data);
    return;
}

void post_order(BinaryTree *tree) {
    printf("post_order(%d) = ", tree->n);
    post_order_Node(tree->root);
    printf("\n");
    return;
}


int main() {
    BinaryTree *tree = init_BinaryTree();
    srand(time(0));
    #define max_op 8
    int val;
    for (int i = 0; i < max_op; i++) {
        val = rand() % 100;
        insert_BinaryTree(tree, val);
    }
    output_BinaryTree(tree);
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    clear_BinaryTree(tree);
    return 0;
}
