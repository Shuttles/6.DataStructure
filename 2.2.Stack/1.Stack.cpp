/*************************************************************************
	> File Name: 2.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月05日 星期六 14时30分16秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Stack {
    int *data;
    int size;
    int top;
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
    if (empty(s)) return 0;
    return s->data[s->top];
}

int expand(Stack *s) {
    int new_size = s->size;
    int *p;
    while (new_size) {
        p = (int *)realloc(s->data, sizeof(int) * (new_size + s->size));
        if (p) break;
        new_size /= 2;
    }
    if (!p) return 0; 
    s->data = p;
    s->size += new_size;
    return 1;
}

int push(Stack *s, int val) {
    if (!s) return 0;
    if (s->top + 1 == s->size) {
        if (!expand(s)) return 0;
        printf("expand the Stack's size successfully\n");
    };
    s->data[++s->top] = val;
    return 1;
}

int pop(Stack *s) {
    if (!s) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

void output(Stack *s) {
    if (!s) return;
    printf("Stack(%d) = [", s->size);
    for (int i = 0; i <= s->top; i++) {
        (i != 0) && printf(", ");
        printf("%d", s->data[i]);
    }
    printf("]\n");
    return;
}

int main() {
    Stack *s = init_Stack(2);
    srand(time(0));
    #define max_op 20
    int op, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to Stack = %d\n", 
                      val, push(s, val));
                output(s);
                printf("\n");
            } break;
            case 3: {
                printf("pop %d from the Stack = ", top(s));
                printf("%d\n", pop(s));
                output(s);
                printf("\n");
            } break;
        }
    
    }
    clear_Stack(s);
    return 0;
}
