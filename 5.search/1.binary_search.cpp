/*************************************************************************
	> File Name: 1.binary_search.cpp
	> Author: 
	> Mail: 
	> Created Time: 四  2/20 20:33:54 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define P(func, args...) {\
    printf("%s = %d\n", #func, func(args));\
}

//1 3 5 7 9 10
int binary_search1(int *arr, int n, int x) {
    int head = 0, tail = n - 1, mid;
    while (head <= tail) {
        mid = (head + tail) >> 1;
        if (arr[mid] == x) return mid;
        if (arr[mid] < x) head = mid + 1;
        else tail = mid - 1;
    }
    return -1;
}

//111111000
int binary_search2(int *arr, int n) {
    int head = -1, tail = n - 1, mid;
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (arr[mid] == 1) head = mid;
        else tail = mid - 1;
    }
    return head;//如果是00000000，则返回-1，妙啊！！
}

//00000001111找第一个1
int binary_search3(int *arr, int n) {
    int head = 0, tail = n, mid;
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (arr[mid] == 1) tail = mid;
        else head = mid + 1;
    }
    return tail == n ? -1 : tail;
}

int main() {
    int arr1[10] = {1, 3, 5, 7, 9, 11, 13, 17, 19, 21};
    int arr2[10] = {1, 1, 1, 1};
    int arr3[10] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
    P(binary_search1, arr1, 10, 7);
    P(binary_search2, arr2, 10);
    P(binary_search3, arr3, 10);
    return 0;
}
