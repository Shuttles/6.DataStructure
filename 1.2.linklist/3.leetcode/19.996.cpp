/************************************************************************
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
    struct ListNode ret, *p = head, *q;
    ret.next = head;
    int length = 0;
    while (p) {
        p = p->next;
        length += 1;
    }
    int ind = length - n;
    p = &(ret);
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    free(q);
    return ret.next;
}
