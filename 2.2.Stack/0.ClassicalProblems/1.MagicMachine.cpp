/*************************************************************************
	> File Name: 1.MagicMachine.cpp
	> Author: 
	> Mail: 
	> Created Time: 五  2/14 17:00:12 2020
 ************************************************************************/

 //这是计蒜客数据结构里的程序设计：蒜头君的魔法机！！！！
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Stack {
    int *data;
    int top, size;
} Stack;

Stack *init_Stack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top = -1;
    return s;
}

void clear_Stack(Stack *s) {
    if (!s) return;
    free(s->data);
    free(s);
    return;
}

int empty(Stack *s) {
    if (!s) return 0;
    return s->top == -1;
}

int top(Stack *s) {
    if (!s) return 0;
    if(empty(s)) return 0;
    return s->data[s->top];
}

int expand(Stack *s) {
    if (!s) return 0;
    int new_size = s->size;
    int *p;
    while (new_size) {
        p = (int *)realloc(s->data, sizeof(int) * (new_size + s->size));
        if (p) break;
        new_size /= 2;
    }
    if (p) {
        s->data = p;
        s->size += new_size;
        return 1;
    }
    return 0;
}

int push(Stack *s, int val) {
    if (!s) return 0;
    if (s->top + 1 == s->size) {
        if (!expand(s)) return 0;
        printf("expand the Stack successfully\n");
    }
    s->data[++s->top] = val;
    return 1;
}

int pop(Stack *s) {
    if (!s) return 0;
    if (empty(s)) return 0;
    s->top--;
    return 1;
}

void output(Stack *s) {
    if (!s) return;
    printf("Stack(%d) = [", s->size);
    for (int i = 0; i <= s->top; i++) {
        i && printf(", ");
        printf("%d", s->data[i]);
    }
    printf("]\n");
    return;
}

#define MAX_N 100
int flag[MAX_N + 5] = {1};

int main() {
    Stack *s = init_Stack(100);
    //push(s, 1);
    int n;
    scanf("%d", &n);
   	for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        if (x == top(s)) {
            pop(s);
            flag[x] = 1;
            printf("x = %d == top(s) flag[%d] = 1\n", x, x);
            output(s);
        } else if (x > top(s)) {
            if (!flag[x - 1]) {
                int ind;
                for (ind = x - 1; flag[ind] == 0; ind--)
                {} //就是这个{}解决了我的困扰了两个小时的问题！！！！
                for (int j = ind + 1; j <= x; j++) {push(s, j);}
                //不能像下面这么干！！！
            	/*for (int j = top(s) + 1; j <= x; j++) {
                	push(s, j);
                }*/
            	pop(s);
            	flag[x] = 1;
                printf("x = %d ind = %d flag[%d] = 1\n", x, ind, x);
                output(s);
            } else {
                flag[x] = 1;
                printf("x = %d flag[%d] = 1, so flag[%d] = 1\n", x, x - 1, x);
                output(s);
                continue;
            }
        } else {
            printf("x = %d top(s) = %d\n", x, top(s));
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    return 0;
}
