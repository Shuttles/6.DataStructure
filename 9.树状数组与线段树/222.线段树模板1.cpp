/*************************************************************************
	> File Name: 222.线段树模板1.cpp
	> Author: 
	> Mail: 
	> Created Time: 一  4/27 20:19:43 2020
 ************************************************************************/

#include<iostream>
using namespace std;

#define MAX_N 10000
#define lc(ind) (ind << 1)
#define rc(ind) (ind << 1 | 1)

struct Node {
    int max_num;
} tree[(MAX_N << 2) + 5];

int root = 1;//线段树根节点下标

int arr[MAX_N + 5];/*存储原数组的值*/

void UP(int ind) {
    tree[ind].max_num = max(tree[lc(ind)].max_num, tree[rc(ind)].max_num);
    return ;
}

void build(int ind, int l, int r) {
    /*当前结点下标、维护的区间范围*/
    if (l == r) {
        tree[ind].max_num = arr[l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(lc(ind), l, mid);
    build(rc(ind), mid + 1, r);
    UP(ind);/*将左右子树的值上提到当前结点*/
    return ;
}

void modify(int ind, int x, int y, int l, int r) {
    /*将x点的值修改为y*/
    if (l == r) {
        /*叶子结点*/
        if (l - x) {
            /*说明x不在区间范围内*/
            return ;
        }
        tree[ind].max_num = y;
        /*建树完成后就没必要改arr数组了*/
        return ;
    }
    int mid = (l + r) >> 1;
    if (x <= mid) modify(lc(ind), x, y, l, mid);
    else modify(rc(ind), x, y, mid + 1, r);
    UP(ind);
    return ;
}

int query(int ind, int x, int y, int l, int r) {
    if (x <= l && r <= y) {
        return tree[ind].max_num;
    }
    int ans = 0x80000000, mid = (l + r) >> 1;
    if (x <= mid) ans = max(ans, query(lc(ind), x, y, l, mid));
    if (y > mid) ans = max(ans, query(rc(ind), x, y, mid + 1, r));
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(root, 1, n);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            modify(root, b, c, 1, n);
        } else {
            cout << query(root, b, c, 1, n) << endl;
        }
    }
    return 0;
}
