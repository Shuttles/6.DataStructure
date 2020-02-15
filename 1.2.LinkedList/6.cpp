/*************************************************************************
	> File Name: 6.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年01月23日 星期四 19时00分05秒
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
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
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
    return ;
}

void clear_LinkedList(LinkedList *l) {
    if (!l) return;
    ListNode *p = &(l->head), *q;//////
    while (p) {
        q = p->next;
        clear_ListNode(p);
        p = q;
    }
    free(l);
    return;
}

int insert(LinkedList *l, int ind, int val) {
    if (!l) return 0;
    if (ind < 0 || ind > l->length) return 0;
    ListNode *p = &(l->head), *node = init_ListNode(val);
    while (ind--) 
        p = p->next;
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

int erase(LinkedList *l, int ind) {
    if (!l) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while (ind--) 
        p = p->next;
    q = p->next;
    p->next = q->next;
    clear_ListNode(q);
    l->length -= 1;
    return 1;
}

void output(LinkedList *l) {
    if (!l) return ;
    printf("LinkedList(%d) = [", l->length);
    ListNode *p = l->head.next;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL]\n");
    return;
}

int main() {
    #define MAX_OP 20
    srand(time(0));
    LinkedList *l = init_LinkedList();
    int op, ind, val;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        ind = rand() % (l->length + 3) - 1;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to LinkedList = %d\n", 
                      val, ind, insert(l, ind, val));
                output(l);
                printf("\n");
            } break;
            case 3: {
                printf("erase element at %d from LinkedList = %d\n", 
                      ind, erase(l, ind));
                output(l);
                printf("\n");
            } break;
        }
    }
    clear_LinkedList(l);
    return 0; 
}
