/*************************************************************************
	> File Name: 4.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月05日 星期六 23时08分12秒
 ************************************************************************/
 //17min打完
 //2019.10.06 16min
 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <math.h>

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

void clear_Queue(Queue *q) {
    if (!q) return;
    free(q->data);
    free(q);
    return;
}

int empty(Queue *q) {
    if (!q) return 0;
    return q->count == 0;
} 

int front(Queue *q) {
    if (!q) return 0;
    return q->data[q->head];
}

int expand(Queue *q) {
    if (!q) return 0;
    int new_size = q->length;
    int *p;
    while (new_size) {
        p = (int *)realloc(q->data, sizeof(int) * (new_size + q->length));
        if (p) break;
        new_size /= 2;
    }
    if (p) {
        q->data = p;
        q->length += new_size;
        return new_size;
    }
    return 0;
}


int push(Queue *q, int val) {
    if (!q) return 0;
    if (q->count == q->length) {
        int offset = abs(expand(q) - q->length);
        if (offset == q->length) return 0;
        printf("expand the Queue successfully\n");
        q->tail += offset;
    };
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
    printf("Queue(%d) = [", q->length);
    for (int i = q->head, j = 0; j < q->count; j++) {
        j && printf(", ");
        printf("%d", q->data[(i + j) % q->length]);
    }
    printf("]\n");
    return;
} 

int main() {
    #define max_op 20
    Queue *q = init_Queue(2);
    int op, val;
    srand(time(0));
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to the Queue = %d\n", 
                      val, push(q, val));
                output(q);
                printf("\n");
            } break;
            case 3: {
                printf("pop %d from the Queue = ", front(q));
                printf("%d\n", pop(q));
                output(q);
                printf("\n");
            } break;
        }
    }
    clear_Queue(q);
     return 0;
 }
