/*************************************************************************
	> File Name: 24.1.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 16时40分55秒
 ************************************************************************/

struct ListNode *swapPairs(struct ListNode *head) {
    struct ListNode ret, *q, *p, *r;
    ret.next = head;
    p = q = &ret;
    p = p->next;
    if (!p) return ret.next;
    q = p->next;
    r = &ret;
    while (p->next) {
        p->next = q->next;
        r->next = q;
        q->next = p;
        if (!p->next) break;
        r = p;
        p = r->next;
        q = p->next;
    }
    return ret.next;
}
