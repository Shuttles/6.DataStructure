/*************************************************************************
	> File Name: 8.binary_search_Tree.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  2/22 16:38:17 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *init_Node(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->lchild = node->rchild = NULL;
    return node;
}

Node *insert(Node *root, int key) {
    if (!root) {
        return init_Node(key);
    }
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (!root) return root;
    if (key < root->key) root->lchild = erase(root->lchild, key);
    else if (key > root->key) root->rchild = erase(root->rchild, key);
    else {
        //删除
        if (root->lchild == NULL || root->rchild == NULL) {
            //度为0或1的结点
            Node *temp = root->rchild ? root->rchild : root->lchild;
            free(root);
            return temp;
        } else {
            //度为2的结点
            //要找到前驱或者后继，此处以前驱为例
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    return root;
}

void clear_Node(Node *root) {
    if (!root) return ;
    clear_Node(root->lchild);
    clear_Node(root->rchild);
    free(root);
    return ;
}

void in_orderNode(Node *root) {
    if (!root) return ;
    in_orderNode(root->lchild);
    printf("%d ", root->key);
    in_orderNode(root->rchild);
    return ;
}

void in_order(Node *root) {
    //if (!root) return;
    printf("in_order : ");
    in_orderNode(root);
    printf("\n");
    return ;
}


int main() {
    int op, val;
    Node *root = NULL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 1: {
                root = insert(root, val);
            } break;
            case 2: {
                root = erase(root, val);
            } break;
        }
        in_order(root);
        //printf("\n");
    }
    clear_Node(root);
    return 0;
}
