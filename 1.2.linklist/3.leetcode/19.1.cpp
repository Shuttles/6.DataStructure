/*************************************************************************
	> File Name: 19.1.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 15时55分42秒
 ************************************************************************/

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *removeNthFromEnd(struct ListNode *head, int n) {
    struct ListNode ret, *p, *q;
    int length = 0;
    ret.next = head;
    p = &ret;
    while (p) {
        length++;
        p = p->next;
    }
    length--;
    p = &ret;
    int pos = length - n;
    while (pos--) {
        p = p->next;
    }
    q = p->next;
    p->next = q->next;
    free(q);
    return ret.next;
}
