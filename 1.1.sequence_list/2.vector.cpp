/*************************************************************************
	> File Name: 2.vector.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年01月22日 星期三 15时27分02秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector *init_vector(int n) {
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * n);
    vec->size = n;
    vec->length = 0;
    return vec;
}

void clear_vector(Vector *vec) {
    free(vec->data);
    free(vec);
    return;
}

int expand(Vector *vec) {
    if (!vec) return 0;
    int new_size = vec->size;
    int *p;
    while (new_size) {
        p = (int *)realloc(vec->data, sizeof(int) * (new_size + vec->size));
        if (p) break;
        new_size /= 2;
    }
    if (!new_size) return 0;
    vec->size += new_size;
    vec->data = p;
    return 1;
}

int insert(Vector *vec, int ind, int val) {
    if (!vec) return 0;
    if (ind < 0 || ind > vec->length) return 0;
    if (vec->length == vec->size) {
        if (!expand(vec)) return 0;
        printf("expand the Vector = (%d) successfully\n", vec->size);
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
    if (!vec) return;
    printf("Vector(%d) = [", vec->size);
    for (int i = 0; i < vec->length; i++) {
        i && printf(", ");
        printf("%d", vec->data[i]);
    }
    printf("]\n");
    return;
}


int main() {
    #define MAX_OP 20
    srand(time(0));
    Vector *vec = init_vector(2);
    int ind, val, op;
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        ind = rand() % (vec->length + 2) - 1;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to Vector = %d\n", 
                       val, ind, insert(vec, ind, val));
                output(vec);
                printf("\n");
            } break;
            case 3: {
                printf("erase element at %d from Vector = %d\n", 
                      ind, erase(vec, ind));
                output(vec);
                printf("\n");
            } break;
        }
    }
    clear_vector(vec);
    return 0;
}
