/*************************************************************************
	> File Name: 286.1.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 15时20分17秒
 ************************************************************************/
int missingNumber(int* nums, int numsSize){
    int ans = 0, n = numsSize + 1;
    for (int i = 0, j = 2; ; i += 1, j *= 2) {
        int cnt = n / j * (j >> 1);
        if (n % j > (j >> 1)) {
            cnt += n % j - (j >> 1);
        }
        if (cnt % 2) ans |= (1 << i);
        if (j >= n) break;
    }
    for (int i = 0; i < numsSize; i++) ans ^= nums[i];
    return ans;
}
