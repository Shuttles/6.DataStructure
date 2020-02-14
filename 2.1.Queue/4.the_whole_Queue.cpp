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
    int head, tail, size, length;
} Queue;

Queue *init_Queue(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->size = n;
    q->head = q->tail = q->length = 0;
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
    return q->length == 0;
} 

int front(Queue *q) {
    if (!q) return 0;
    return q->data[q->head];
}

int expand(Queue *q) {
    if (!q) return 0;
    int extra_size = q->size;
    int *p;
    while (extra_size) {
        p = (int *)realloc(q->data, sizeof(int) * (extra_size + q->size));
        if (p) break;
        extra_size /= 2;
    }
    if (!p) return 0; 
    q->data = p;
    int previous_size = q->size;
    q->size += extra_size;
    if (q->head < q->tail) return 1;//如果是正常顺序
    //非正常顺序
    /*
    for (int i = 0; i < extra_size; i++) {
        int ind = previous_size;
        for (int j = ind; j < q->size; j++) {
            for (int k = j; k > q->head; k--) {
                q->data[k] = q->data[k - 1];
                q->head++;
            }
        }
    }
    */
    int ind = q->size - 1;
    for (int i = previous_size - 1; i >= q->head; i--) {
        q->data[ind--] = q->data[i];
    }
    q->head += extra_size;
    return 1;
}


int push(Queue *q, int val) {
    if (!q) return 0;
    if (q->size == q->length) {
        if (!expand(q)) return 0;
        printf("expand the Queue successfully\n");
    };
    q->data[q->tail++] = val;
    if (q->tail == q->size) q->tail -= q->size;
    q->length++;
    return 1;
}

int pop(Queue *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    q->head++;
    if (q->head == q->size) q->head -= q->size;
    q->length--;
    return 1;
}

void output(Queue *q) {
    if (!q) return;
    printf("Queue(%d) = [", q->length);
    for (int i = q->head, j = 0; j < q->length; j++) {
        j && printf(", ");
        printf("%d", q->data[(i + j) % q->size]);
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
