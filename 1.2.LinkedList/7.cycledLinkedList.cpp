/*************************************************************************
	> File Name: 7.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年01月23日 星期四 22时33分08秒
 ************************************************************************/
//
//19min
//15min 2020.1.25
//14min 2020.1.26
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
    ListNode *r = l->head.next, *p = l->head.next, *q;
    p = p ? p->next : NULL;//为了防止链表为空
    while (p != r) { //终止条件必须是p == r !!!!!!因为这是循环链表！！
        q = p->next;
        clear_ListNode(p);
        p = q;
    }
    if (p) clear_ListNode(p);  //如果链表为空，那么p也为空，就不必clear了！
    free(l);
    return ;
}

int insert(LinkedList *l, int ind, int val) {
    ListNode *q = init_ListNode(val);
    //如果链表为空, 那么插入的节点就为尾结点！！当然这也可看成头结点！！
    if (!l->head.next) {
        if (ind != 0) return 0;
        l->head.next = q;
        q->next = q;//指向自己
        l->length += 1;
        return 1;
    }
    //if (l->length == 1 && ind = 1) return 0;//当只有一个尾结点时只能让ind = 0的插入！！
    if (ind < 0 || ind > l->length) return 0;
    int ret = ind;//暂存ind信息
    ListNode *p = l->head.next;  //*q = init_ListNode(val);
    while (ind--) p = p->next;
    q->next = p->next;
    p->next = q;
    if (ret == l->length) l->head.next = q;//如果插入到尾部的话要移动虚拟头的指向！！
    l->length += 1;
    return 1;
} 

int erase(LinkedList *l, int ind) {
    if (!l) return 0;
    if (ind < 0 || ind >= l->length) return 0;
    ListNode *p = l->head.next, *q;
    int ret = ind;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    clear_ListNode(q);
    //if (l->length == 1) l->head.next = NULL;//如果删除了唯一一个结点的话
    if (ret == l->length - 1) l->head.next = p;//如果删除了尾结点，head.next要移到前一个
    l->length -= 1;
    if (l->length == 0) l->head.next = NULL;//如果删除之后链表为空，那就让head.next = NULL，否则不知道会指向哪！！！
    return 1;
}

void output(LinkedList *l) {
    if (!l) return;
    printf("LinkedList(%d) = [", l->length);
    ListNode *p = l->head.next ? l->head.next->next : l->head.next;//如果链表不为空就指向0号节点，为空就指向NULL；
    int len = l->length;
    while (len--) {//不能像单链表那样用while (p)了！
        printf("%d->", p->data);
        p = p->next;
    }
    if (l->length != 0)
        printf("%d]\n", l->head.next->next->data);//为显示出循环链表，让0号结点最后也输出一次!
    else printf("]\n");
    return;
}

int main() {
    #define MAX_OP 10
    srand(time(0));
    LinkedList *l = init_LinkedList();
    int ind, val, op;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
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
                printf("erase element at %d from the LinkedList = %d\n", 
                      ind, erase(l, ind));
                output(l);
                printf("\n");
            } break;
        }
    }
    clear_LinkedList(l);
    return 0; 
}
