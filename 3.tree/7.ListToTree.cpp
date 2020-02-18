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
    free(root);
    return;
}

void clear_Tree(Tree *tree) {
    if (!tree) return ;
    clear_Node(tree->root);
    free(tree);
    return ;
}

Stack *init_Stack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * n);
    s->top = -1;
    s->size = n;
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
    Node *temp = NULL, *root = NULL;//root记录最后的根节点
    Stack *s = init_Stack(strlen(str));
    int flag = 0;//记录有无逗号
    int i = 0;
    while (str[i]) {
        switch (str[i]) {
            case '(': {//只有遇到左括号，前一个值才入栈！！！因为左括号表示这是一个新事件的开始！！即后面是前一个值的子树！！！
                push(s, temp);
                flag = 0;
                temp = NULL;
            } break;
            case ')': {
                root = top(s);
                pop(s);
            } break;
            case ',': {
                flag = 1;
                temp = NULL;
            } break;
            case ' ': break;
            default: {
                temp = init_Node(str[i]);
                //为什么要判空呢？因为这时可能是根节点！！！
                if (!empty(s) && !flag) {
                    top(s)->lchild = temp;
                } else if (!empty(s) && flag) {
                    top(s)->rchild = temp;
                }
                (*node_num)++;
            } break;
        }
        ++i;
    }
    clear_Stack(s);
    if (temp && !root) root = temp;//防止只有一个根节点，如A
    return root;
}

void pre_orderNode(Node *root) {
    if (!root) return ;
    printf("%c ", root->data);
    pre_orderNode(root->lchild);
    pre_orderNode(root->rchild);
    return ;
}

void pre_order(Tree *tree) {
    if (!tree) return ;
    printf("pre_order : ");
    pre_orderNode(tree->root);
    printf("\n");
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
    if (!tree) return;
    printf("in_order : ");
    in_orderNode(tree->root);
    printf("\n");
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
    if (!tree) return ;
    printf("post_order : ");
    post_orderNode(tree->root);
    printf("\n");
    return;
}

void outputNode(Node *root) {
    if (!root) return;
    printf("%c", root->data);
    if (!root->lchild && !root->rchild) return ;
    printf("(");
    outputNode(root->lchild);
    if (root->rchild) printf(",");
    outputNode(root->rchild);
    printf(")");
    return ;
}

void output(Tree *tree) {
    if (!tree) return ;
    outputNode(tree->root);
    printf("\n");
    return ;
}


int main() {
    char str[100];
    scanf("%[^\n]s", str);
    int node_num = 0;
    Tree *tree = init_Tree();
    tree->root = transform(str, &node_num);
    tree->n = node_num;
    output(tree);
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    clear_Tree(tree);
    return 0;
}
