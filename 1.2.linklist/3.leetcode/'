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
    struct ListNode *p = head, *q = head;
    if (!p) return false;
    do {
        p = p->next;
        q = q->next;
        if (!q || !q->next) return false;//if中的条件极为重要！！ 
        q = q->next;
    } while (p != q);
    return true;
}
