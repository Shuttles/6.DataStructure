/*************************************************************************
	> File Name: 234.1.cpp
	> Author: 
	> Mail: 
	> Created Time: 三  2/12 23:35:24 2020
 ************************************************************************/
 /*
* Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


bool isPalindrome(struct ListNode* head){
    int64_t a = 0, b = 0;
    struct ListNode ret, *p = head, *q;
    ret.next = NULL;
    while (p) {
        q = p->next;
        p->next = ret.next;
        ret.next = p;
        a = a * 10 + p->val;
        p = q;
    }
    p = ret.next;
    while (p) {
        b = b * 10 + p->val;
        p = p->next;
    }
    return a == b;
}
