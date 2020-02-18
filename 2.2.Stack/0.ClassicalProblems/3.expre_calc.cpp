/*************************************************************************
	> File Name: 3.expre_calc.cpp
	> Author: 
	> Mail: 
	> Created Time: 二  2/18 14:25:10 2020
 ************************************************************************/

#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
#define MAX_N 100

int calc(const char *str, int l, int r) {
    int prior = 0x3f3f3f3f - 1, temp = 0, pos = -1;
    for (int i = l; i <= r; i++) {
        int cur_prior = 0x3f3f3f3f;
        switch (str[i]) {
            case '(': temp += 100; break;
            case ')': temp -= 100; break;
            case '+':
            case '-': cur_prior = temp + 1; break;
            case '*':
            case '/': cur_prior = temp + 2; break;
            case '^': cur_prior = temp + 3; break;
        }
        if (cur_prior <= prior) {
            pos = i;
            prior = cur_prior;
        }
    }
    if (pos == -1) {
        int num = 0;
        for (int i = l; i <= r; i++) {
            if (str[i] < '0' || str[i] > '9') continue; 
            num = num * 10 + str[i] - '0';
        }
        return num;
    }
    int a = calc(str, l, pos - 1);
    int b = calc(str, pos + 1, r);
    switch (str[pos]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return (int)pow(a, b);
    }
    return 0;
}


int main() {
    char str[MAX_N + 5] = {0};
    while (~scanf("%[^\n]s", str)) {
        getchar();
        printf("%d\n", calc(str, 0, strlen(str) - 1));
    }
    return 0;
}
