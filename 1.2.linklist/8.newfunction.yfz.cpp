/*************************************************************************
	> File Name: 7.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年01月23日 星期四 22时33分08秒
 ************************************************************************/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct LinkedList {
    ListNode head;
    int length;
} LinkedList;

ListNode *init_ListNode(int val) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = val;
    node->next = NULL;
    return node;
}

LinkedList *init_LinkedList() {
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

void clear_ListNode(ListNode *node) {
    if (!node) return ;
    free(node);
    return;
}

void clear_LinkedList(LinkedList *l) {
    if (!l) return;
    ListNode *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_ListNode(p);
        p = q;
    }
    free(l);
    return ;
}

int insert(LinkedList *l, int ind, int val) {
    if (!l) return -1;
    if (ind < 0 || ind > l->length) return -1;
    int ret = ind;
    ListNode *p = &(l->head), *q = init_ListNode(val);
    while (ind--) p = p->next;
    q->next = p->next;
    p->next = q;
    l->length += 1;
    return ret;
} 

int erase(LinkedList *l, int ind) {
    if (!l) return -1;
    if (ind < 0 || ind >= l->length) return -1;
    ListNode *p = &(l->head), *q;
    int ret = -1;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    clear_ListNode(q);
    l->length -= 1;
    return ret;
}

int search(LinkedList *l, int val) {
    int ind = 0;
    ListNode *p = l->head.next;
    while (p && p->data != val) {
        p = p->next;
        ind++;
    }
    if (ind == l->length) ind = -1;
    return ind;
}


void output(LinkedList *l) {
    if (!l) return;
    printf("head->");
    ListNode *p = l->head.next;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL\n");
    return;
}

void output_search(LinkedList *l, int ind) {
    char str[100];
    int offset = 3;
    ListNode *p = l->head.next;
    while (ind != -1) {
        offset += sprintf(str, "%d->", p->data);
        ind -= 1;
        p = p->next;
    }
    for (int i = 0; i < offset; i++) printf(" ");
    printf("^\n");
    for (int i = 0; i < offset; i++) printf(" ");
    printf("|\n\n");
    return;
}

int main() {
    #define MAX_OP 20
    srand(time(0));
    LinkedList *l = init_LinkedList();
    int ind, val, op, flag;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        ind = rand() % (l->length + 3) - 1;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to the LinkedList\n", 
                      val, ind);
                flag = insert(l, ind, val);
            } break;
            case 3: {
                printf("erase element at %d from the LinkedList\n", 
                      ind);
                flag = erase(l, ind);
            } break;
        }
        output(l);
        output_search(l, flag);
    }
    return 0; 
}
