/*************************************************************************
	> File Name: 2.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月05日 星期六 14时09分47秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int head, tail, length, count;
} Queue;

Queue *init_Queue(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->length = n;
    q->head = q->tail = q->count = 0;
    return q;
}

int empty(Queue *q) {
    if (!q) return 0;
    return q->count == 0;
} 

int front(Queue *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    return q->data[q->head];    
}

void clear_Queue(Queue *q) {
    if (!q) return;
    free(q->data);
    free(q);
    return ;
}

int push(Queue *q, int val) {
    if (!q) return 0;
    if (q->count == q->length) return 0;
    q->data[q->tail++] = val;
    if (q->tail == q->length) q->tail -= q->length;
    q->count++;
    return 1;
}

int pop(Queue *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    q->head++;
    if (q->head == q->length) q->head -= q->length;
    q->count--;
    return 1;
}

void output(Queue *q) {
    if (!q) return;
    printf("Queue(%d) = [", q->count);
    for (int i = q->head, j = 0; j < q->count; j++) {
        j && printf(", ");
        printf("%d", q->data[(i + j) % q->length]);
    }
    printf("]\n");
    return;
} 

int main() {
    #define max_op 20
    Queue *q = init_Queue(5);
    srand(time(0));
    int op, ind, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        val = rand() % 100;
        switch (op) {
            case 2:
            case 3:
            case 0: {
                printf("push %d to Queue = %d\n", 
                      val, push(q, val));
                output(q);
                printf("\n");
            } break;
            case 1: {
                printf("pop %d from Queue = ", front(q));
                printf("%d\n", pop(q));
                output(q);
                printf("\n");
            } break;
        }
    }
    clear_Queue(q);
    return 0;
}

