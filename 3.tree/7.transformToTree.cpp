/*************************************************************************
	> File Name: 7.transformToTree.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  2/15 20:32:05 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    Node *root;
    int n;
} Tree;

typedef struct Stack {
    Node **data;
    int top, size;
} Stack;

Node *init_Node(char val) {
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


void clear_Node(Node *root) {
    if (!root) return;
    clear_Node(root->lchild);
    clear_Node(root->rchild);
    return;
}

void clear_tree(Tree *tree) {
    if (!tree) return ;
    clear_Node(tree->root);
    free(tree);
    return ;
}

Stack *init_Stack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * n);
    s->top = -1;
    s->size = 0;
    return s;
}

int empty(Stack *s) {
    if (!s) return 0;
    return s->top == -1;
}

Node *top(Stack *s) {
    return s->data[s->top];
}

void clear_Stack(Stack *s) {
    if (!s) return;
    free(s->data);
    free(s);
    return;
}

int push(Stack *s, Node *val) {
    if (!s) return 0;
    if (s->top + 1 == s->size) return 0;
    s->data[++s->top] = val;
    return 1;
} 

int pop(Stack *s) {
    if (empty(s)) return 0;
    --s->top;
    return 1;
}

Node *transform(char *str, int *node_num) {
    Node *temp = NULL, *p = NULL;
    Stack *s = init_Stack(strlen(str));
    int flag = 0;//记录有无逗号
    while (str[0]) {
        switch (str[0]) {
            case '(': {
                push(s, temp);
                flag = 0;
                temp = NULL;
            } break;
            case ')': {
                p = top(s);
                pop(s);
            } break;
            case ',': {
                flag = 1;
                temp = NULL;
            } break;
            case ' ':break;
            default: {
                temp = init_Node(str[0]);
                if (!empty(s) && flag == 0) {
                    top(s)->lchild = temp;
                } else if (!empty(s) && flag == 1) {
                    top(s)->rchild = temp;
                }
                (*node_num)++;
            } break;
        }
        ++str;
    }
    clear_Stack(s);
    if (temp && !p) p = temp;
    return p;
}

void pre_orderNode(Node *root) {
    if (!root) return ;
    printf("%c ", root->data);
    pre_orderNode(root->lchild);
    pre_orderNode(root->rchild);
    return ;
}

void pre_order(Tree *tree) {
    printf("pre_order : [");
    pre_orderNode(tree->root);
    printf("]\n");
    return;
}

void in_orderNode(Node *root) {
    if (!root) return ;
    in_orderNode(root->lchild);
    printf("%c ", root->data);
    in_orderNode(root->rchild);
    return ;
}

void in_order(Tree *tree) {
    printf("in_order : [");
    in_orderNode(tree->root);
    printf("]\n");
    return;
}

void post_orderNode(Node *root) {
    if (!root) return ;
    post_orderNode(root->lchild);
    post_orderNode(root->rchild);
    printf("%c ", root->data);
    return ;
}

void post_order(Tree *tree) {
    printf("post_order : [");
    post_orderNode(tree->root);
    printf("]\n");
    return;
}


int main() {
    char str[100];
    scanf("%[^\n]s", str);
    int node_num = 0;
    Tree *tree = init_Tree();
    tree->root = transform(str, &node_num);
    tree->n = node_num;
    pre_order(tree), printf("\n");
    in_order(tree), printf("\n");
    post_order(tree), printf("\n");
    clear_tree(tree);
    return 0;
}
