/*************************************************************************
	> File Name: 2.heap_sort.cpp
	> Author: 
	> Mail: 
	> Created Time: 二  2/18 19:24:40 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) {\
    __typeof(a) __temp = a;\
    a = b; b = __temp;\
}

void down_update(int *arr, int n, int ind) {
    while ((ind << 1) <= n) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (arr[l] > arr[temp]) temp = l;
        if (r <= n && arr[r] > arr[temp]) temp = r;
        if (temp == ind) break;
        swap(arr[temp], arr[ind]);
        ind = temp;
    }
    return ;
}

void heap_sort(int *arr, int n) {
    --arr;//骚操作
    //下面是建大顶堆
    for (int i = n >> 1; i >= 1; i--) {
        down_update(arr, n, i);
    }
    //出堆
    for (int i = n; i > 1; i--) {
        swap(arr[i], arr[1]);
        down_update(arr, i - 1, 1);
    }
    return ;
}

void output(int *arr, int n) {
    printf("arr(%d) = [", n);
    for (int i = 0; i < n; i++) {
        i && printf(" ");
        printf("%d", arr[i]);
    }
    printf("]\n");
    return;
}

int main() {
    srand(time(0));
    #define MAX_OP 20
    int *arr = (int *)malloc(sizeof(int) * MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        arr[i] = val;
    }
    output(arr, MAX_OP);
    heap_sort(arr, MAX_OP);
    output(arr, MAX_OP);
    free(arr);
    return 0;
}
