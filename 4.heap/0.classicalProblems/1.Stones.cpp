/*************************************************************************
	> File Name: 1.Stones.cpp
	> Author: 
	> Mail: 
	> Created Time: 三  2/19 20:19:07 2020
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b), (b) = __temp;\
}


typedef struct Stone {
    int p, d;
} Stone;

typedef struct Heap {
    Stone *data;
    int cnt, size;
} Heap;

Heap *init_Heap(int n) { 
    Heap *q = (Heap *)malloc(sizeof(Heap));
    q->data = (Stone *)malloc(sizeof(Stone) * (n + 1));
    q->cnt = 0;
    q->size = n;
    return q;
}

void clear_Heap(Heap *q) {
    if (!q) return ;
    free(q->data);
    free(q);
    return;
}

int empty(Heap *q) {
    return q->cnt == 0;
}

Stone top(Heap *q) {
    return q->data[1];
}

//这个函数极为关键！！！
int cmp_Stone(Stone a, Stone b) {
    if (a.p < b.p) return 1;
    if (a.p == b.p && a.d < b.d) return 1;
    return 0;
}

void down_update(Heap *q, int n, int ind) {
    if (!q) return ;
    while ((ind << 1) <= n) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (cmp_Stone(q->data[l], q->data[temp])) temp = l;
        if (r <= n && cmp_Stone(q->data[r], q->data[temp])) temp = r;
        if (temp == ind) break;
        swap(q->data[temp], q->data[ind]);
        ind = temp;
    }
    return ;
}

int pop(Heap *q) {
    if (!q) return 0;
    if (empty(q)) return 0;
    q->data[1] = q->data[q->cnt--];
    down_update(q, q->cnt, 1);
    return 1;
}

int push(Heap *q, Stone s) {
    if (!q) return 0;
    if (q->cnt == q->size) return 0;
    q->data[++q->cnt] = s;
    int ind = q->cnt;
    while ((ind >> 1) && cmp_Stone(q->data[ind], q->data[ind >> 1])) {
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
}


int main() {
    int N;
    scanf("%d", &N);
    while (N--) {
        int n;
        scanf("%d", &n);
        Heap *q = init_Heap(n);
        for (int i = 0; i < n; i++) {
            Stone s;
            scanf("%d%d", &s.p, &s.d);
            push(q, s);
        }
        int distance = 0, sum = 1;
        while (!empty(q)) {
            Stone s = top(q);
            pop(q);
            distance = s.p;
            if (sum % 2) {
                s.p += s.d;
                push(q, s);
            }
            ++sum;
            //sum记录遇到的第几个石子
        }
        printf("%d\n", distance);
        clear_Heap(q);
    }
    return 0;
}
