/*************************************************************************
	> File Name: 202.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 15时18分00秒
 ************************************************************************/
int get_next(int x) {
    int temp = 0;
    while (x) {
        temp += (x % 10) * (x % 10);
        x /= 10;
    }
    return temp;
}

bool isHappy(int n) {
    int p = n, q = n;
    while (q != 1) {
        p = get_next(p);
        q = get_next(get_next(q));
        if (p == q) break;
    }
    return (q == 1);
}
