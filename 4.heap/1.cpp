/*************************************************************************
	> File Name: 3.cpp
	> Author: 
	> Mail: 
	> Created Time: 三  2/19 11:44:26 2020
 ************************************************************************/

//19min, 2020.2.19
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

typedef struct Heap {
    int *data;
    int cnt, size;
} Heap;

Heap *init_Heap(int n) {
    Heap *q = (Heap *)malloc(sizeof(Heap));
    q->data = (int *)malloc(sizeof(int) * (n + 1));
    q->cnt = 0;
    q->size = n;
    return q;
}

void clear_Heap(Heap *q) {
    if (!q) return ;
    free(q->data);
    free(q);
    return ;
}

int empty(Heap *q) {
    return q->cnt == 0;
}

int top(Heap *q) {
    return q->data[1];
}

int push(Heap *q, int val) {
    if (!q) return 0;
    if (q->cnt == q->size) return 0;
    q->data[++q->cnt] = val;
    //下面是自本身到父结点的向上调整
    int ind = q->cnt;
    while ((ind >> 1) && q->data[ind] > q->data[ind >> 1]) {
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
} 

int pop(Heap *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];
    //下面是自父结点到左右孩子的向下调整
    int ind = 1;
    while ((ind << 1) <= q->cnt) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (q->data[l] > q->data[temp]) temp = l;
        if (r <= q->cnt && q->data[r] > q->data[temp]) temp = r;
        if (temp == ind) break;//如果父结点比左右孩子都大，调整就结束了
        swap(q->data[temp], q->data[ind]);
        ind = temp;
    } 
    return 1;
}


int main() {
    #define MAX_N 10
    srand(time(0));
    Heap *q = init_Heap(MAX_N);
    for (int i = 0; i < MAX_N; i++) {
        int val = rand() % 100;
        push(q, val);
        printf("push %d to the Heap\n", val);
    }
    for (int i = 0; i < MAX_N; i++) {
        printf("%d ", top(q));
        pop(q);
    }
    printf("\n");
    clear_Heap(q);
    return 0;
}
