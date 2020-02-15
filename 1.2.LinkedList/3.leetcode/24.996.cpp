/*************************************************************************
	> File Name: 24.1.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 16时40分55秒
 ************************************************************************/

struct ListNode *swapPairs(struct ListNode *head) {
    struct ListNode ret, *q, *p;
    ret.next = head;
    p = &ret;
    q = p->next;
    while (q && q->next) {
        p->next = q->next;
        q->next = p->next->next;
        p->next->next = q;
        p = q;
        q = q->next;
    }
    return ret.next;
}
