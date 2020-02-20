/*************************************************************************
	> File Name: 3.cpp
	> Author: 
	> Mail: 
	> Created Time: 四  2/20 16:15:58 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define swap(a, b) {\
    a ^= b;\
    b ^= a;\
    a ^= b;\
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


void insert_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
            swap(arr[j], arr[j - 1]);
        }
    }
    return ;
}

void bubble_sort(int *arr, int n) {
    int times = 1;
    for (int i = 1; i < n && times; i++) {
        times = 0;
        for (int j = 0; j < n - i; j++) {
            if (arr[j] <= arr[j + 1]) continue;
            swap(arr[j], arr[j + 1]);
            times++;
        }
    }
    return;
}

void merge_sort(int *arr, int l, int r) {
    if (r - l <= 1) {//达到可解决问题的规模
        if (r - l == 1 && arr[l] > arr[r]) {
            swap(arr[l], arr[r]);
        }
        return ;
    }
    int mid = (l + r) >> 1;
    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int p1 = l, p2 = mid + 1, k = 0;
    while (p1 <= mid || p2 <= r) {
        if (p2 > r || (p1 <= mid && arr[p1] <= arr[p2])) {
            temp[k++] = arr[p1++];
        } else {
            temp[k++] = arr[p2++];
        }
    }
    memcpy(arr + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return;
}

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
    #define MAX_OP 10
    int arr[MAX_OP];
    randint(arr, MAX_OP);
    TEST(arr, MAX_OP, insert_sort, num, MAX_OP);
    TEST(arr, MAX_OP, bubble_sort, num, MAX_OP);
    TEST(arr, MAX_OP, merge_sort, num, 0, MAX_OP - 1);
    return 0;
}
