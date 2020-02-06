/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月02日 星期三 15时21分11秒
 ************************************************************************/
// 1h6min 2019.11.9 愁了1h，发现不能free(p)！！！！
// 23min 2019.11.10
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Vector {
    int *data;
    int length, size;
} Vector;

Vector *init(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int * )malloc(sizeof(int) * n);
    vec->size = n;
    vec->length = 0;
    return vec;
}

int expand(Vector *vec) {
    if (!vec) return 0;
    int new_size = vec->size;
    int *p;
    while (new_size) {
        p = (int *)realloc(vec->data, sizeof(int) * (vec->size + new_size));
        if (p) break;
        new_size /= 2;
    }
    if (!p) return 0;
    vec->size += new_size;
    vec->data = p;
    //free(p);  经过实验发现 不能free(p)！！！！
    return 1;
}

int insert(Vector *vec, int ind, int val) {
    if (!vec) return 0;
    if (vec->length == vec->size) {
        if (!expand(vec)) return 0;
        printf("expand Vector size to %d successfully\n", vec->size);
    }
    if (ind < 0 || ind > vec->length) return 0;
    for (int i = vec->length; i > ind; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[ind] = val;
    vec->length += 1;
    return 1;
}

int erase(Vector *vec, int ind) {
    if (!vec) return 0;
    //if (!vec->length) return 0;  发现不需要这行代码
    if (ind < 0 || ind >= vec->length) return 0;
    for (int i = ind + 1; i < vec->length; i++) {
        vec->data[i - 1] = vec->data[i];
    }
    vec->length -= 1;
    return 1;
}

void clear(Vector *vec) {
    if (!vec) return ;
    free(vec->data);
    free(vec);
    return ;
}

void output(Vector *vec) {
    if (!vec) return ;
    printf("Vector(%d) = [", vec->size);
    for (int i = 0; i < vec->length; i++) {
        i && printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
    return ;
}

int main() {
    srand(time(0));
    Vector *vec = init(1);
    #define max_op 20
    int op, ind, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        ind = rand() % (vec->length + 3) - 1;
        val = rand() % 100;
        switch (op) {
            case 2:
            case 3:
            case 0: {
                printf("insert %d at  %d to Vector = %d\n",
                       val, ind, insert(vec, ind ,val));
                output(vec);
                printf("\n");
            } break;
            case 1:{
                printf("erase element at %d from Vector = %d\n",
                      ind, erase(vec, ind));
                output(vec);
                printf("\n");
            } break;
        }
    }
    clear(vec);
    return 0;
}
