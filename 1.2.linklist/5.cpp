/*************************************************************************
	> File Name: 5.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月04日 星期五 20时41分12秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct LinkedList {
    struct ListNode head;
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

void clear_ListNode (ListNode *node) {
    if (!node) return;
    free(node);
    return;
}

void clear_LinkedList(LinkedList *l) {
    if (!l) return;
    ListNode *p = &(l->head), *q;
    p = p->next;
    while (p) {
        q = p->next;
        clear_ListNode(p);
        p = q;
    }
    free(l);
    return ;
}

int insert(LinkedList *l, int ind, int val) {
    if (!l) return 0;
    if (ind < 0 || ind > l->length) return 0;
    ListNode *p = &(l->head), *node = init_ListNode(val), *q;
    while (ind--) {
        p = p->next;
    }
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

int erase(LinkedList *l, int ind) {
    if (!l) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    clear_ListNode(q);
    l->length -= 1;
    return 1;
}

void output(LinkedList *l) {
    if (!l) return;
    printf("LinkedList(%d) = [", l->length);
    ListNode *p = &(l->head);
    p = p->next;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL]\n");
    return;
}

void reverse(LinkedList *l) {
    if (!l) return;
    ListNode *p, *q;
    p = &(l->head);
    p = p->next;
    l->head.next = NULL;
    while (p) {
        q = p->next;
        p->next = l->head.next;
        l->head.next = p;
        p = q;
    }
    return ;
}

int main() {
    LinkedList *l = init_LinkedList();
    #define max_op 20
    srand(time(0));
    int op, val, ind;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 5;
        ind = rand() % (l->length + 3) - 1;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to the LinkedList = %d\n", 
                      val, ind, insert(l, ind, val));
                output(l);
                printf("\n");
            } break;
            case 3: {
                printf("erase item at %d from the LinkedList = %d\n", 
                      ind, erase(l, ind));
                output(l);
                printf("\n");
            } break;
            case 4: {
                printf("reverse the LinkedList\n");
                reverse(l);
                output(l);
                printf("\n");
            } break;
        }
    }
    return 0;
}
