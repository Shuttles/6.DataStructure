/*************************************************************************
	> File Name: 3.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年01月23日 星期四 14时07分57秒
 ************************************************************************/
//20min,致命错误在于52行那个==写成了=
//19min 2020.1.23
//17min 2020.1.24
//15min 2020.1.25
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector *init_Vector(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * n);
    vec->size = n;
    vec->length = 0;
    return vec;
}

void clear_Vector(Vector *vec) {
    if (!vec) return;
    free(vec->data);
    free(vec);
    return ;
}

int expand(Vector *vec) {
    if (!vec) return 0;
    int extre_size = vec->size;
    int *p;
    while (extre_size) {
        p = (int *)realloc(vec->data, sizeof(int) * (extre_size + vec->size));
        if (p) break;
        extre_size /= 2;
    }
    if (!p) return 0;
    vec->size += extre_size;
    vec->data = p;
    return 1;
}

int insert(Vector *vec, int ind, int val) {
    if (!vec) return 0;
    if (ind < 0 || ind > vec->length) return 0;
    if (vec->length == vec->size) {
        if (!expand(vec)) return 0;
        printf("expand Vector = (%d) successfully\n", vec->size);
    }
    for (int i = vec->length; i > ind; i--) {
        vec->data[i] = vec->data[i - 1];
    }
    vec->data[ind] = val;
    vec->length += 1;
    return 1;
}


int erase(Vector *vec, int ind) {
    if (!vec) return 0;
    if (ind < 0 || ind >= vec->length) return 0;
    for (int i = ind; i < vec->length - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->length -= 1;
    return 1;
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
    #define MAX_OP 20
    srand(time(0));
    Vector *vec = init_Vector(3);
    int ind, val, op;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        ind = rand() % (vec->length + 3) - 1;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to the Vector = %d\n", 
                      val, ind, insert(vec, ind, val));
                output(vec);
                printf("\n");
            } break;
            case 3: {
                printf("erase element at %d from the Vector = %d\n", 
                      ind, erase(vec, ind));
                output(vec);
                printf("\n");
            } break;
        }
    }
    clear_Vector(vec);
    return 0;
}
