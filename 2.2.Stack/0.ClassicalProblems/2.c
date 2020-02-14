/*************************************************************************
	> File Name: 2.cpp
	> Author: 
	> Mail: 
	> Created Time: 五  2/14 17:53:44 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Stack {
    char *data;
    int top, size;
} Stack;

Stack *init_Stack(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (char *)malloc(sizeof(char) * n);
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

/*
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
*/

int push(Stack *s, char val) {
    if (!s) return 0;
    if (s->top + 1 == s->size) {
        //if (!expand(s)) return 0;
        //printf("expand the Stack successfully\n");
        return 0;
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

/*
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
*/


int main() {
    Stack *s = init_Stack(30);
    char str1[24];
    char str2[24];
    scanf("%s", str1);
    int len1 = strlen(str1) - 1;

    for (int i = 0; i < len1; i++) {
        push(s, str1[i]);
    }


    for (int i = s->top, j = 0; i >= 0; i--) {
        str2[j++] = s->data[i];
        pop(s);
    }
    str1[len1] = '\0';
    printf("str1 = %s\nstr2 = %s\n", str1, str2);
    printf("%s\n", (strcmp(str1, str2) == 0) ? "true" : "false");
    clear_Stack(s);
    return 0;
}
