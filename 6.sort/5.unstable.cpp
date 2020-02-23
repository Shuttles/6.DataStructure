/*************************************************************************
	> File Name: 5.cpp
	> Author: 
	> Mail: 
	> Created Time: 四  2/20 18:31:23 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//用^的话必须a和b不能是同一个变量(而不是同一个数)！！！
#define swap(a, b) {\
    __typeof(a) __temp = (a);\
    (a) = (b); (b) = __temp;\
}

#define TEST(arr, n, func, args...) {\
    int *num = (int *)malloc(sizeof(int) * n);\
    memcpy(num, arr, sizeof(int) * n);\
    output(num, n);\
    printf("%s = ", #func);\
    func(args);\
    output(num, n);\
    free(num);\
}


void select_sort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int ind = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[ind]) ind = j;
        }
        if (ind - i) swap(arr[i], arr[ind]);
    }
    return ;
}

void quick_sort(int *arr, int l, int r) {
    if (r < l) return ;
    int x = l, y = r, z = arr[l];
    while (x < y) {
        while (x < y && arr[y] >= z) y--;
        if (x < y) arr[x++] = arr[y];
        while (x < y && arr[x] <= z) x++;
        if (x < y) arr[y--] = arr[x];
    }
    arr[x] = z;
    quick_sort(arr, l, x - 1);
    quick_sort(arr, x + 1, r);
    return;
}

/*
void quick_sort(int *num, int l, int r) {
    while (l < r) {
        int x = l, y = r, z = num[(l + r) >> 1];
        do {
            while (x <= y && num[x] < z) x++;
            while (x <= y && num[y] > z) y--;
            if (x <= y) {
                swap(num[x], num[y]);
                x++, y--;
            }
        } while (x <= y);
        quick_sort(num, x, r);
        r = y;
    }
    return ;
}
*/
void randint(int *arr, int n) {
    while (n--) arr[n] = rand() % 100;
    return ;
}

void output(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        i && printf(", ");
        printf("%d", arr[i]);
    }
    printf("]\n");
    return ;
}


int main() {
    srand(time(0));
    #define MAX_OP 20
    int arr[MAX_OP];
    randint(arr, MAX_OP);
    TEST(arr, MAX_OP, select_sort, num, MAX_OP);
    output(arr, MAX_OP);
    TEST(arr, MAX_OP, quick_sort, num, 0, MAX_OP - 1);
    return 0;
}
