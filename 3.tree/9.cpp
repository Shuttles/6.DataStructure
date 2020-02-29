/*************************************************************************
	> File Name: 9.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  2/29 22:31:21 2020
 ************************************************************************/

#include<iostream>
using namespace std;

int transform(int *arr) {
    arr[4] = 5;
    return 1;
}

int main() {
    int a[5] = {0, 1, 2, 3, 4};
    printf("a[4] = %d\n", a[4]);
    transform(a);
    printf("a[4] = %d\n", a[4]);
    return 0;
}
