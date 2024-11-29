#include <stdio.h>

int sum_of_numbers (int *nums, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += nums[i];
    }
    return sum;
}


int sum_by_recursion(int *nums, int pos, int len) {
    if (pos == len - 1) {
        return nums[pos];
    } else {
        return nums[pos] + sum_by_recursion(nums, pos + 1, len);
    }
}


int main(int argc, char const *argv[]) {
    int nums[] ={1, 3, 5, 6, 4, 6};
    int res = sum_by_recursion(nums, 0, 6);
    printf("%d\n", res);
    return 0;
}
