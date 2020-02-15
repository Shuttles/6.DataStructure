/*************************************************************************
	> File Name: 203.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 15时18分17秒
 ************************************************************************/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode ret, *p = &ret, *q;
    ret.next = head;
    while (p && p->next) {
        while (p->next->val == val) {
            q = p->next;
            p->next = q->next;
            free(q);
            if (!p->next) return ret.next;
        }
        p = p->next;
    }
    return ret.next;
}
