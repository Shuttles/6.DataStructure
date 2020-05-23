/*************************************************************************
	> File Name: 1.TwoSumSmaller.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2020年05月23日 星期六 19时42分31秒
 ************************************************************************/

#include <iostream>
using namespace std;

int two_sum_smaller(int *nums, int n, int target) {
    if (n <= 1) return 0;
    int head = 0, tail = n - 1, ans = 0;
    while (head < tail) {
        while (head < tail && nums[head] + nums[tail] < target) head++;
        if (head == tail) break;
        ans += head;
        tail--;
    }
    ans += (head + 1) * head / 2;
    return ans;
}
