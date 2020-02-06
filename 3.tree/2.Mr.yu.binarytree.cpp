/*************************************************************************
	> File Name: 1.tree.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月19日 星期二 18时54分24秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Binary_Tree {
    Node *root;
    int n;
} Binary_Tree;

Node *init_Node(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

Binary_Tree *init_BinaryTree() {
    Binary_Tree *tree = (Binary_Tree *)malloc(sizeof(Binary_Tree));
    tree->root = NULL;
    tree->n = 0;
    return tree;
}

void clear_Node(Node *node) {
    if (!node) return;
    clear_Node(node->lchild);
    clear_Node(node->rchild);
    free(node);
    return;
}

void clear_BinaryTree(Binary_Tree *tree) {
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
    if (root->data > val) root->lchild = insert_Node(root->lchild, val, flag);
    else root->rchild = insert_Node(root->rchild, val, flag);
    return root;
}

void insert(Binary_Tree *tree, int val) {
    int flag = 0;
    tree->root = insert_Node(tree->root, val, &flag);
    tree->n += flag;
    return;
}

void output_Node(Node *root) {
    if (!root) return;
    printf("%d", root->data);
    //if (!root->lchild && !root->rchild) return;
    printf("(");
    output_Node(root->lchild);
    printf(",");
    output_Node(root->rchild);
    printf(")");
    return;
}

void output_BinaryTree(Binary_Tree *tree) {
    if (!tree) return;
    printf("Binary_Tree(%d) = ", tree->n);
    output_Node(tree->root);
    printf("\n");
    return;
}

void in_order_Node(Node *node) {
    if (!node) return;
    in_order_Node(node->lchild);
    printf("%d ", node->data);
    in_order_Node(node->rchild);
    return;
}

void in_order(Binary_Tree *tree) {
    printf("in_order(%d) = ", tree->n);
    in_order_Node(tree->root);
    printf("\n");
    return;
}

void pre_order_Node(Node *node) {
    if (!node) return;
    printf("%d ", node->data);
    pre_order_Node(node->lchild);
    pre_order_Node(node->rchild);
    return;
}

void pre_order(Binary_Tree *tree) {
    printf("pre_order(%d) = ", tree->n);
    pre_order_Node(tree->root);
    printf("\n");
    return;
}

void post_order_Node(Node *node) {
    if (!node) return;
    post_order_Node(node->lchild);
    post_order_Node(node->rchild);
    printf("%d ", node->data);
    return;
}

void post_order(Binary_Tree *tree) {
    printf("post_order(%d) = ", tree->n);
    post_order_Node(tree->root);
    printf("\n");
    return;
}

int main() {
    #define max_op 5
    srand(time(0));
    int val;
    Binary_Tree *tree = init_BinaryTree();
    for (int i = 0; i < max_op; i++) {
        val = rand() % 100;
        insert(tree, val);
    }
    output_BinaryTree(tree);
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    clear_BinaryTree(tree);
    return 0;
}
