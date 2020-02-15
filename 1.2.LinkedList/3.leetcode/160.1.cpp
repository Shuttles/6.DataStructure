/*************************************************************************
	> File Name: 160.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 15时17分40秒
 ************************************************************************/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *p = headA, *q = headB, *r = NULL;    
    int flag1 = 1, flag2 = 1, flag3 = 1;
    while (p && q) {//1st版写的是p->next && q->next,这样不能判断空链表和只有一个元素的链表(踩过的两个坑)
        if (p == q && flag3) {//1st没写flag3，后来意识到如果不特判，相遇后会p和q会一直相等(踩过的第一个坑)
            r = q;
            flag3 = 0;
        }
        p = p->next;
        q = q->next;//1st版写在了while里的一开头(坑)
        if (!p && flag1) {//1st版写的是p->next(坑)
            p = headB;
            flag1 = 0;
        }
        if (!q && flag2) {
            q = headA;
            flag2 = 0;
        }
    }
    return r;
}
