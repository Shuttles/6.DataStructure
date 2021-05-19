/*************************************************************************
	> File Name: 3.hashtable_czy.c
	> Author: 少年宇
	> Mail: 
	> Created Time: 2021年05月19日 星期三 19时34分09秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_N 100

typedef struct Node {
    char *str;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node **data;
    int size;
} HashTable;


Node *init_node(char *str, Node *head) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->str = strdup(str);
    p->next = head;
    return p;
}

HashTable *init_hashtable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;
    h->data = (Node **)calloc(sizeof(Node *), h->size);
    return h;
}

void clear_node(Node *node) {
    if (!node) return ;
    Node *p = node, *q;
    while (p) {
        q = p->next;
        free(p->str);
        free(p);
        p = q;
    }
    free(q);
    return ;
}

void clear_hashtable(HashTable *h) {
    if (!h) return ;
    for (int i = 0; i < h->size; i++) clear_node(h->data[i]);
    free(h->data);
    free(h);
    return ;
}


//hash function
int BKDRHash(char *str) {
    int seed = 31, hash = 0;
    for (int i = 0; str[i]; i++) {
        hash = hash * seed + str[i];
    }
    return hash & 0x7fffffff;
}


int insert(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    h->data[ind] = init_node(str, h->data[ind]);
    return 1;
}

int search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    Node *p = h->data[ind];
    while (p && strcmp(p->str, str)) {
        p = p->next;
    }
    return p != NULL;
}

int main() {
    int op;
    char str[MAX_N + 5];
    HashTable *h = init_hashtable(MAX_N + 5);
    while (~scanf("%d%s", &op, str)) {
        switch (op) {
            case 0: {
                printf("insert %s to HashTable!\n", str);
                insert(h, str);
            } break;
            case 1: {
                printf("search %s from HashTable, result = %d\n", str, search(h, str));
            } break;
        }
    }
    clear_hashtable(h);
    return 0;
}
