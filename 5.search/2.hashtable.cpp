/*************************************************************************
	> File Name: 2.hashtable.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  2/22 15:02:29 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
    char *str;
    struct ListNode *next;
} ListNode;

typedef struct HashTable {
    ListNode **data;
    int size;
} HashTable;

ListNode *init_ListNode(char *str, ListNode *head) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->str = strdup(str);//将原来str字符串拷贝出来
    p->next = head;
    return p;
}

HashTable *init_HashTable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1;//开两倍的空间
    h->data = (ListNode **)calloc(h->size, sizeof(ListNode *));
    return h;
}

void clear_ListNode(ListNode *node) {
    if (!node) return ;
    ListNode *p = node, *q;
    while (p) {
        q = p->next;
        free(p->str);
        free(p);
        p = q;
    }
    free(q);
    return ;
}

void clear_HashTable(HashTable *h) {
    if (!h) return ;
    for (int i = 0; i < h->size; i++) {
        clear_ListNode(h->data[i]);
    }
    free(h->data);
    free(h);
}

int BKDRHash(char *str) {
    int seed = 31, hash = 0;//hash为最后返回值
    for (int i = 0; str[i]; i++) hash = (hash * seed + str[i]);
    return hash & 0x7fffffff;
}

int insert(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    h->data[ind] = init_ListNode(str, h->data[ind]);
    return 1;
}

int search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    ListNode *p = h->data[ind];
    while (p && strcmp(p->str, str)) {
        p = p->next;
    } 
    return p != NULL;
}

int main() {
    int op;
    #define MAX_N 100
    char str[MAX_N + 5];
    HashTable *h = init_HashTable(MAX_N + 5);
    while (~scanf("%d%s", &op, str)) {
        switch (op) {
            case 0: {
                printf("insert %s to the HashTable\n", str);
                insert(h, str);
            } break;
            case 1: {
                printf("search %s in the HashTable = %d\n", 
                      str, search(h, str));
            } break;
            printf("\n");
        }
    }
    clear_HashTable(h);
    return 0;
}
