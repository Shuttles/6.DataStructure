/*************************************************************************
	> File Name: 286.2.cpp
	> Author: 少年宇
	> Mail: 
	> Created Time: 2019年10月03日 星期四 15时20分34秒
 ************************************************************************/
int missingNumber(int* nums, int numsSize){
    for (int i = 0; i < numsSize; i++) {
        while (nums[i] != i && nums[i] != numsSize) {
            int a = nums[i], b = nums[nums[i]];
            nums[a] = a, nums[i] = b;
        }
    }
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] - i) return i;
    }
    return numsSize;
}
