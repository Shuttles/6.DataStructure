/*************************************************************************
	> File Name: 223.线段树模板2.cpp
	> Author: 
	> Mail: 
	> Created Time: 一  4/27 20:19:43 2020
 ************************************************************************/

#include<iostream>
#include <cinttypes>
using namespace std;

#define MAX_N 10000
#define lc(ind) (ind << 1)
#define rc(ind) (ind << 1 | 1)
#define tag(ind) tree[ind].tag
#define cnt(ind) tree[ind].cnt
#define sum(ind) tree[ind].sum

struct Node {
    int64_t sum;
    int cnt;/*这个结点所维护的区间长度*/
    int64_t tag;
} tree[(MAX_N << 2) + 5];

int root = 1;//线段树根节点下标

int64_t arr[MAX_N + 5];/*存储原数组的值*/

void UP(int ind) {
    tree[ind].sum = tree[lc(ind)].sum + tree[rc(ind)].sum;
    return ;
}

void DOWN(int ind) {
    if (tree[ind].tag) {
        tag(lc(ind)) += tag(ind);
        tag(rc(ind)) += tag(ind);
        sum(lc(ind)) += tag(ind) * cnt(lc(ind));
        sum(rc(ind)) += tag(ind) * cnt(rc(ind));
        tag(ind) = 0;
    }
    return ;
}

void build(int ind, int l, int r) {
    /*当前结点下标、维护的区间范围*/
    tree[ind].cnt = (r - l + 1);
    tree[ind].tag = 0;  
    if (l == r) {
        tree[ind].sum = arr[l];
        return ;
    }

    int mid = (l + r) >> 1;
    build(lc(ind), l, mid);
    build(rc(ind), mid + 1, r);
    UP(ind);/*在递归后上提，将左右子树的值上提到当前结点*/
    return ;
}

/*区间修改*/
void modify(int ind, int x, int y, int64_t d, int l, int r) {
    /*将x~y的值统统+d*/
    if (x <= l && r <= y) {
        /*叶子结点*/
        tree[ind].tag += d;/*一定是+=!!!!*/
        tree[ind].sum += (tree[ind].cnt * d);
        return ;
    }
    DOWN(ind);/*在递归前下沉*/
    int mid = (l + r) >> 1;
    if (x <= mid) modify(lc(ind), x, y, d, l, mid);
    if (y > mid) modify(rc(ind), x, y, d, mid + 1, r);
    UP(ind);/*在递归后上提*/
    return ;
}

int64_t query(int ind, int x, int y, int l, int r) {
    if (x <= l && r <= y) {
        return tree[ind].sum;
    }
    DOWN(ind);/*在递归前下沉*/
    int64_t ans = 0, mid = (l + r) >> 1;
    if (x <= mid) ans += query(lc(ind), x, y, l, mid);
    if (y > mid) ans += query(rc(ind), x, y, mid + 1, r);
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    build(root, 1, n);

    for (int i = 0; i < m; i++) {
        int64_t a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            int64_t d;
            cin >> d;
            modify(root, b, c, d, 1, n);
        } else {
            cout << query(root, b, c, 1, n) << endl;
        }
    }
    return 0;
}
