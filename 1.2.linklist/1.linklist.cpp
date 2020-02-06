/*************************************************************************
	> File Name: 1.linklist.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月02日 星期三 17时48分15秒
 ************************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct LinkList {
    ListNode head;
    int length;
} LinkList;

ListNode *init_ListNode(int val) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->data = val;
    node->next = NULL;
    return node;
}

LinkList *init_linklist() {
    LinkList *l = (LinkList *)malloc(sizeof(LinkList));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

void clear_listnode(ListNode * node) {
    if (!node) return;
    free(node);
    return ;
}

void clear_linklist(LinkList *l) {
    if (!l) return ;
    ListNode *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_listnode(p);
        p = q;
    }
    free(l);
    return ;
}

int insert(LinkList *l, int ind, int val) {
    if (!l) return 0;
    if (ind < 0 || ind > l->length) return 0;
    ListNode *p = &(l->head), *node = init_ListNode(val);
    while (ind--) {
        p = p->next;
    }
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;
}

int erase(LinkList *l, int ind) {
    if (!l) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while (ind--) {
        p = p->next;
    }
    q = p->next;
    p->next = q->next;
    clear_listnode(q);
    l->length -= 1;
    return 1;
}

void output(LinkList *l) {
    if (!l) return;
    printf("LinkList(%d) = [", l->length);
    ListNode *p = l->head.next;
    while (p) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("NULL]\n");
    return ;
}

void reverse(LinkList *l) {
    if (!l) return;
    ListNode *q, *p = &(l->head);
    p = p->next;
    l->head.next = NULL;
    while (p) {
        q = p->next;
        p->next = l->head.next;
        l->head.next = p;
        p = q;
    }
    return;
}

int main() {
    LinkList *l = init_linklist();
    #define max_op 20
    srand(time(0));
    int op, ind, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 5;
        ind = rand() % (l->length + 3) - 1;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to LinkList = %d\n",
                      val, ind, insert(l, ind, val));
                output(l);
                printf("\n");
            } break;
            case 3: {
                printf("erase item at %d from LinkList = %d\n",
                      ind, erase(l, ind));
                output(l);
                printf("\n");
            } break;
            case 4: {
                printf("reverse the LinkList\n");
                reverse(l);
                output(l);
                printf("\n");
            } break;
        }
    }
    return 0;
}




