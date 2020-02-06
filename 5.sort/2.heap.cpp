/*************************************************************************
	> File Name: 2.heap.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年12月03日 星期二 00时33分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(a, b) {\
    __typeof(a) temp = a;\
    a = b; b = temp;\
}

void downUpdate(int *arr, int n, int ind) {
    while ((ind << 1) <= n) {
        int max_val = ind, lchild = ind << 1, rchild = ind << 1 | 1;
        if (arr[max_val] < arr[lchild]) max_val = lchild;
        if (rchild <= n && arr[max_val] < arr[rchild]) max_val = rchild;
        if (max_val == ind) break;
        swap(arr[ind], arr[max_val]);
        ind = max_val;
    }
    return ;
}

void heap_sort(int *arr, int n) {
    arr -= 1;
    //建堆
    for (int i = n >> 1; i >= 1; i--) {
        downUpdate(arr, n, i);
    }
    //排序
    for (int i = n; i > 1; i--) {
        swap(arr[1], arr[i]);
        downUpdate(arr, i - 1, 1);
    }
    return;
}

void output(int *arr, int n) {
    printf("arr[%d] = [", n);
    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf("]\n");
    return;
}

int main() {
    srand(time(0));
    #define max_op 20
    int *arr = (int *)malloc(sizeof(int) * max_op);
    for (int i = 0; i < max_op; i++) {
        arr[i] = rand() % 100;
    }
    output(arr, max_op);
    heap_sort(arr, max_op);
    output(arr, max_op);
    free(arr);
    return 0;
}
