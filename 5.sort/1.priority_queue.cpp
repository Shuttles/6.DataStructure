/*************************************************************************
	> File Name: 1.heap.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年12月02日 星期一 22时48分18秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define log(frm, args...) {\
    printf("[%s : %s : %d] ", __FILE__, __func__, __LINE__);\
    printf(frm, ##args);\
    printf("\n");\
}
#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}


typedef struct priority_queue {
    int *data;
    int cnt, size;
} priority_queue;

priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (int *)malloc(sizeof(int) * (n + 1));
    q->size = n;
    q->cnt = 0;
    return q;
}

void clear(priority_queue *q) {
    if (!q) return;
    free(q->data);
    free(q);
    return;
}

int empty(priority_queue *q) {
    return q->cnt == 0;
}

int top(priority_queue *q) {
    return q->data[1];
}

int push(priority_queue *q, int val) {
    if (!q) return 0;
    if (q->cnt == q->size) return 0;
    q->cnt += 1;
    q->data[q->cnt] = val;
    int ind = q->cnt;
    while (ind >> 1 && q->data[ind] > q->data[ind >> 1]) {
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}

int pop(priority_queue *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    swap(q->data[1], q->data[q->cnt]);
    q->cnt--;
    int ind = 1;
    while (ind << 1 <= q->cnt) {
        int max_val = ind, lchild = ind << 1, rchild = ind << 1 | 1;
        if (q->data[lchild] > q->data[max_val]) max_val = lchild;
        if (rchild <= q->cnt && q->data[rchild] > q->data[max_val]) max_val = rchild;
        if (max_val == ind) break;
        swap(q->data[ind], q->data[max_val]);
        ind = max_val;
    }
    return 1;
} 

int main() {
    #define max_op 20
    priority_queue *q = init(max_op);
    srand(time(0));
    for (int i = 0; i < max_op; i++) {
        int val = rand() % 100;
        printf("push %d to the priority_queue\n", val);
        push(q, val);
    }
    for (int i = 0; i < max_op; i++) {
        printf("%d ", top(q));
        pop(q);
    }
    clear(q);
    return 0;
}
