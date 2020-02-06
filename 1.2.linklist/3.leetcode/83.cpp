/*************************************************************************
	> File Name: 83.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 15时17分03秒
 ************************************************************************/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *p = head, *q;
    while (p && p->next) {
        q = p->next;//写在while里防止head==NULL；
        if (p->val == p->next->val) {
            p->next = q->next;
            free(q);
        } else {
            p = p->next;
        }
    }
    return head;
}
