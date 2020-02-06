/*************************************************************************
	> File Name: 3.haffman.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年11月22日 星期五 22时33分22秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define max_n 1000
#define swap(a, b) {\
    __typeof(a) temp = a;\
    a = b, b = temp;\
}

typedef struct Node {
    char ch;
    double p; //代表当前结点出现的概率
    struct Node *next[2]; 
} Node;

typedef struct Code {
    char ch;
    char *str;
} Code;

typedef struct HaffmanTree {
    Node *root;
    int n; //到底有多少种字符
    Code *codes;
} HaffmanTree;

typedef struct Data {
    char ch;
    double p;
} Data;

Data arr[max_n + 5];

Node *getNewNode(Data *obj) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->ch = (obj ? obj->ch : 0);
    p->p = (obj ? obj->p : 0);
    p->next[0] = p->next[1] = NULL;
    return p;
}

HaffmanTree *getNewTree(int n) {
    HaffmanTree *tree = (HaffmanTree *)malloc(sizeof(HaffmanTree));
    tree->codes = (Code *)malloc(sizeof(Code) * n);
    tree->root = NULL;
    tree->n = n;
    return tree;
}

void insertOnce(Node **arr, int n) {
    for (int j = n; j >= 1; j--) {
        if (arr[j]->p > arr[j - 1]->p) {
            swap(arr[j], arr[j - 1]);
            continue;
        }
        break;
    }
    return;
}

int extractCodes(Node *root, Code *arr, int k, int l, char *buff) {
    buff[l] = 0;
    if (root->next[0] == NULL && root->next[1] == NULL) {
        //如果这个结点是叶子结点
        arr[k].ch = root->ch;
        arr[k].str = strdup(buff);
        return 1;
    }
    int delta = 0; //在相关子树中编码了多少个字符
    buff[l] = '0';
    delta += extractCodes(root->next[0], arr, k + delta, l + 1, buff);//在左子树中编码了多少字符
    buff[l] = '1';
    delta += extractCodes(root->next[1], arr, k + delta, l + 1, buff); //在右子树中编码了多少字符
    return delta;
}

HaffmanTree *build(Data *arr, int n) {
    //形参为装有待编码字符及其频次的数组 还有编码字符的个数
    Node **nodes = (Node **)malloc(sizeof(Node *) * n);
    for (int i = 0; i < n; i++) {
        nodes[i] = getNewNode(arr + i);
    }
    //插入排序，由出现概率从大到小排序
    for (int i = 1; i < n; i++) {
        insertOnce(nodes, i);
    }
    //进行结点提取
    for (int i = n - 1; i >= 1; i--) {
        Node *p = getNewNode(NULL);
        p->next[0] = nodes[i];
        p->next[1] = nodes[i - 1];
        p->p = p->next[0]->p + p->next[1]->p;
        nodes[i - 1] = p;
        insertOnce(nodes, i - 1);
    }
    char *buff = (char *)malloc(sizeof(char) * n);
    HaffmanTree *tree = getNewTree(n);
    tree->root = nodes[0];          //至此haffmantree基本建立完成
    //下面就是读取每个结点的编码存入haffmantree的codes字段中
    extractCodes(tree->root, tree->codes, 0, 0, buff);
    free(nodes);
    free(buff);
    return tree;
}

int main() {
    int n;
    char str[10];
    scanf("%d", &n);
    //输入
    for (int i = 0; i < n; i++) {
       scanf("%s%lf", str, &arr[i].p);
       arr[i].ch = str[0];
    }
    //建立HaffmanTree,传入参数为arr数组(要编码的字符和出现的频次)和要编码的字符个数n
    HaffmanTree *tree = build(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%c : %s\n", tree->codes[i].ch, tree->codes[i].str);
    }
    printf("%lf\n", tree->root->p);
    return 0;
}
