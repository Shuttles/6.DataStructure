/*************************************************************************
	> File Name: 6.异或.cpp
	> Author: 
	> Mail: 
	> Created Time: 四  2/20 19:06:28 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define swap(a, b) {\
    a ^= b; b ^= a; a ^= b;\
}


int main() {
    int a, b;
    while (~scanf("%d", &a)) {
        printf("a = %d, a = %d\n", a, a);
        swap(a, a);
        printf("a = %d, a = %d\n", a, a);
    }
    //这充分说明了用异或来进行swap的话，不能swap(a, a)！！！！
    //快排里的swap不能用这种方法！！！想一想为什么！！
    return 0;
}
