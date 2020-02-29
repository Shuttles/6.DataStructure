/*************************************************************************
	> File Name: 5.binaryTree.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  2/15 16:00:18 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    Node *root;
    int n;
} Tree;

Node *init_Node(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

Tree *init_Tree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
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

void clear_Tree(Tree *tree) {
    if (!tree) return;
    clear_Node(tree->root);
    free(tree);
    return;
}


Node *insertNode(Node *root, int val, int *flag) {
    if (!root) {
        *flag = 1;
        return init_Node(val);
    }
    if (root->data == val) return root;
    if (val < root->data) root->lchild = insertNode(root->lchild, val, flag);
    else root->rchild = insertNode(root->rchild, val, flag);
    return root;
}

/*
int insertNode(Node *root, int val) {
  if (!root) {
    root = 
    return 1;
  }
  if (val == root->data) return 0;
  if (val < root->data) insertNode(root->lchild, val);
  else insertNode(root->rchild, val);
  return 1;
}
*/

/*
 //刘晨旭版，也是不对的，想想为啥呢？
 //还是形参和实参的问题！！！
Node *insertNode(Node *root, int val, int *flag) {
    if (!root) {
        *flag = 1;
        return root = init_Node(val);
    }
    if (root->data == val) return root;
    if (val < root->data) insertNode(root->lchild, val, flag);
    else insertNode(root->rchild, val, flag);
    return root;
}
*/

/*
int i = 0;

int insertNode(Node *root, int val) {
    if (!root) {
        root = init_Node(val); 
        //printf("第%d次插入\n", ++i);
        return 1;
    }
    if (root->data == val) return 0;
    if (val < root->data) insertNode(root->lchild, val);
    else insertNode(root->rchild, val);
    return 1;
}
*/

void insert(Tree *tree, int val) {
    int flag = 0;//用来判断是否插入成功
    tree->root = insertNode(tree->root, val, &flag);
    tree->n += flag;
    return ;
}

void pre_orderNode(Node *root) {
    if (!root) return;
    printf("%d ", root->data);
    pre_orderNode(root->lchild);
    pre_orderNode(root->rchild);
    return ;
}


void pre_order(Tree *tree) {
    printf("pre_order : ");
    pre_orderNode(tree->root);
    printf("\n");
}


void in_orderNode(Node *root) {
    if (!root) return;
    in_orderNode(root->lchild);
    printf("%d ", root->data);
    in_orderNode(root->rchild);
    return ;
}


void in_order(Tree *tree) {
    printf("in_order : ");
    in_orderNode(tree->root);
    printf("\n");
}

void post_orderNode(Node *root) {
    if (!root) return;
    post_orderNode(root->lchild);
    post_orderNode(root->rchild);
    printf("%d ", root->data);
    return ;
}


void post_order(Tree *tree) {
    printf("post_order : ");
    post_orderNode(tree->root);
    printf("\n");
}

void outputNode(Node *root) {
    if (!root) return;
    printf("%d", root->data);
    if (!root->lchild && !root->rchild) return ;
    printf("(");
    outputNode(root->lchild);
    if (root->rchild) printf(","); //如果有右子树，就输个","
    outputNode(root->rchild);
    printf(")");
    return ;
}

void output(Tree *tree) {
    printf("Tree(%d) = ", tree->n);
    outputNode(tree->root);
    printf("\n");
    return ;
}


int main() {
    srand(time(0));
    #define MAX_OP 10
    Tree *tree = init_Tree();
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        insert(tree, val);
        output(tree);
    }
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    clear_Tree(tree);
    return 0;
}
