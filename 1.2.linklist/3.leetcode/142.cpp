/*************************************************************************
	> File Name: 142.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 15时19分29秒
 ************************************************************************/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    if (!head) return head;
    struct ListNode *p = head, *q = head;
    do {
        p = p->next;
        q = q->next;
        if (!q || !q->next) return NULL;
        q = q->next;
    } while (p != q);
    struct ListNode *r = head;
    while (q != r) {
        q = q->next;
        r = r->next;
    }
    return q;
}
