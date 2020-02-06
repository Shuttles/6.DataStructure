/*************************************************************************
	> File Name: 141.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 15时17分20秒
 ************************************************************************/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head) {
    if (!head) return false;
    struct ListNode *p = head, *q = p->next;
    while (p && q) {
        if (p == q) return true;
        p = p->next;
        q = q->next;
        if (!p || !q) return false;
        q = q->next;
    }
    return false;
}
