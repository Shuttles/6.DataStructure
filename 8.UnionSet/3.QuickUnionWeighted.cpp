/*************************************************************************
	> File Name: 1.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  2/22 20:18:54 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct UnionSet {
    int *father, *size;//结点个数
    int n;
} UnionSet;

UnionSet *init_UnionSet(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->father = (int *)malloc(sizeof(int) * (n + 1));
    u->size = (int *)malloc(sizeof(int) * (n + 1));
    u->n = n;
    for (int i = 1; i <= n; i++) {
        u->father[i] = i;
        u->size[i] = 1;
    }
    return u;
}

int find(UnionSet *u, int x) {
    if (u->father[x] == x) return x;
    return find(u, u->father[x]);//妙啊！！！
}

//将a，b进行联通
int merge(UnionSet *u, int a, int b) {
    int fa = find(u, a), fb = find(u, b);
    if (fa == fb) return 0;
    if (u->size[fa] > u->size[fb]) {
        u->father[fb] = fa;
        u->size[fa] += u->size[fb];
    } else {
        u->father[fa] = fb;
        u->size[fb] += u->size[fa];
    }
    return 1;
}

void clear_UnionSet(UnionSet *u) {
    if (!u) return ;
    free(u->father);
    free(u->size);
    free(u);
    return ;
}



int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    UnionSet *u = init_UnionSet(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        switch (a) {
            case 1: {
                merge(u, b, c);
            } break;
            case 2: {
                printf("%s\n", find(u, b) == find(u, c) ? "Yes" : "No");
            } break;
        }
    }
    clear_UnionSet(u);
    return 0;
}
