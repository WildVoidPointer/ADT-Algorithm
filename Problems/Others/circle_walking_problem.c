/* 
Description:
    Numbers from 1 to `n` are arranged in a circle, connected end-to-end. 
    Given a step size `p`, start from 1 and move forward `p` units at a time 
    until you land on a position that has already been visited. 
    Record all the positions visited and sort them in ascending order. 
    What is the `k`-th number in this sorted sequence? 
    (If there are fewer than k numbers, output `-1`).
*/
 

#include <stdio.h>


static void print_integers(int n, int nums[n]) {

    for (int i = 0; i < n; i++) {
        printf("%d  ", nums[i]);
    }

    printf("\n");

}


static void swap_int(int nums[], int a_pos, int b_pos) {
    int tmp = nums[a_pos];
    nums[a_pos] = nums[b_pos];
    nums[b_pos] = tmp;
}


static void quick_sort_int(int nums[], int lower, int upper) {

    if (upper <= lower) {
        return;
    }

    int mid = (lower / 2) + (upper / 2);

    int left = lower;
    int right = upper;

    while (left <= right) {

        while (left <= right && nums[left] > nums[mid]) {
            left++;
        }

        while (left <= right && nums[right] < nums[mid]) {
            right--;
        }

        if (left <= right) {
            swap_int(nums, left, right);
            left++;
            right--;
        }
    }

    quick_sort_int(nums, left, upper);
    quick_sort_int(nums, lower, right);
}


static int gcd_of_int(int num_a, int num_b) {
    if (num_b > 0) {
        return gcd_of_int(num_b, num_a % num_b);
    } else {
        return num_a;
    }
}


static int calculate_track_length(int n, int p) {
    return n / gcd_of_int(n, p);
}


static void circle_walking(
    int n, int numbers[n], int track_len, 
    int track[track_len], int p
) {

    int track_idx = 0;
    int nums_idx = 0;

    track[track_idx++] = numbers[0];   // 起始位置 1

    while (track_idx < track_len) {  // 防止越界
        int next_idx = (nums_idx + p) % n;

        if (next_idx == 0) {  // 回到起点 1 就停止
            return;
        }

        track[track_idx++] = numbers[next_idx];
        nums_idx = next_idx;
    }
}


static void walking_numbers_init(int numbers[], int n) {
    for (int i = 0; i < n; i++) {
        numbers[i] = i + 1;
    }
}


static void default_entrance(int n, int p, int k) {

    int numbers[n];

    int track_len = calculate_track_length(n, p);

    int track[track_len];

    walking_numbers_init(numbers, n);

    circle_walking(n, numbers, track_len, track, p);    

    print_integers(track_len, track);

    quick_sort_int(track, 0, track_len - 1);

    if (k >= track_len) {
        printf("%d\n", -1);
    } else {
        printf("%d\n", track[k]);
    }
}


int main() {
    default_entrance(6, 4, 3);
}
