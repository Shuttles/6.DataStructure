/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 日  2/23 19:44:54 2020
 ************************************************************************/

#include<stdio.h>

void swap(int *p1, int *p2) {
    int *p = p1;
    p1 = p2;
    p2 = p;
    return ;
}

int main() {
    int a = 10, b = 20;
    printf("The old values: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("The new values : a = %d, b = %d\n", a, b);
    return 0;
}
