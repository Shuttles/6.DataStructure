/*************************************************************************
	> File Name: 11.RBT.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  5/16 14:28:24 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1
#define DBLACK 2

typedef struct Node {
    int key;
    int color;//0 red, 1 black, 2 double black
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
    NIL->color = BLACK;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->color = RED;/*默认是红色，因为黑色一定引起失衡*/
    return p;
}

void clear(Node *root) {
    if (root == NIL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

bool has_red_child(Node *root) {
    return root->lchild->color == 0 || root->rchild->color == 0;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}


Node *insert_maintain(Node *root) {
    /*root应该是祖父结点*/
    if (!has_red_child(root)) return root;
    /*root一定是黑色*/

    if (root->lchild->color == RED && root->rchild->color == RED) {
        /*这个if是为了省事而写的！！！*/
        if (!has_red_child(root->lchild) && !has_red_child(root->rchild)) return root;//海贼红黑树单加的一行
        root->color = RED;
        root->lchild->color = root->rchild->color = BLACK;
        return root;
    }
    /*root左右孩子为一黑一红*/
    if (root->lchild->color == RED) {
        if (!has_red_child(root->lchild)) return root;
        /*情况二*/
        if (root->lchild->rchild->color == RED) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);

    } else {
        if (!has_red_child(root->rchild)) return root;
        /*情况二*/
        if (root->rchild->lchild->color == RED) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }  
    /*改成红上顶*/
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}

Node *erase_maintain(Node *root) {
    /*root应该为父节点*/
    if (root->lchild->color != DBLACK && 
        root->rchild->color != DBLACK) return root;
    if (has_red_child(root)) {
        /*说明双重黑的brother是红色*/
        root->color = RED;/*把原来的根节点改成红色*/
        if (root->lchild->color == RED) {
            root = right_rotate(root);
            root->rchild = erase_maintain(root->rchild);
        } else {
            root = left_rotate(root);
            root->lchild = erase_maintain(root->lchild);
        }
        root->color = BLACK;/*把新的根节点变成黑色*/
        return root;
    }
    
    if ((root->lchild->color == DBLACK && !has_red_child(root->rchild)) || 
        (root->rchild->color == DBLACK && !has_red_child(root->lchild))) {
            /*情况一*/
            root->color += 1;
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            return root;
        }
    if (root->rchild->color == BLACK) {
        if (root->rchild->rchild->color != RED) {
            /*RL类型*/
            root->rchild->color = RED;
            root->rchild = right_rotate(root->rchild);
            root->rchild->color = BLACK;
        }

        root->rchild->color = root->color;
        root->color = BLACK;/*38*/
        root->lchild->color -= 1;
        root = left_rotate(root);
        root->rchild->color = BLACK;
    } else {
        if (root->lchild->lchild->color != RED) {
            /*LR类型*/
            root->lchild->color = RED;
            root->lchild =left_rotate(root->lchild);
            root->lchild->color = BLACK;
        }

        root->lchild->color = root->color;
        root->color = BLACK;
        root->rchild->color -= 1;
        root = right_rotate(root);
        root->lchild->color = BLACK; 
    }
    return root;
}


Node *predeccessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *__erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key > key) {
        root->lchild = __erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        if (root->lchild == NIL || root->rchild == NIL) {
            /*度为0或1*/
            /*找到唯一自孩子*/
            Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            /*度为2*/
            /*转换成度为0或1*/
            Node *temp = predeccessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}

Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = __insert(root->lchild, key);
    else root->rchild = __insert(root->rchild, key);
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    /*此为根节点*/
    root->color = BLACK;
    return root;
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d | %d, %d, %d)\n", root->color, root->key, 
           root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}

void in_order(Node *root) {
    if (root == NIL) return ;
    in_order(root->lchild);
    printf("%d %d %d %d\n", root->key, root->color, 
          root->lchild->key, root->rchild->key);
    in_order(root->rchild);
    return ;
}

int main() {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
            case 3: in_order(root); break;
        }
    }

    return 0;
}
