/* 
From:
    https://leetcode.com/problems/magnetic-force-between-two-balls/description/

Description:
    In the universe Earth C-137, Rick discovered a special form of magnetic force between two balls 
    if they are put in his new invented basket. Rick has n empty baskets, the ith basket is at position[i], 
    Morty has m balls and needs to distribute the balls into the baskets 
    such that the minimum magnetic force between any two balls is maximum.
    Rick stated that magnetic force between two different balls at positions x and y is |x - y|.

    Given the integer array position and the integer m. Return the required force.


Example 1:
    Input: position = [1,2,3,4,7], m = 3
    Output: 3
    Explanation: 
        Distributing the 3 balls into baskets 1, 4 and 7 
        will make the magnetic force between ball pairs [3, 3, 6]. 
        The minimum magnetic force is 3. 
        We cannot achieve a larger minimum magnetic force than 3.


Example 2:
    Input: position = [5,4,3,2,1,1000000000], m = 2
    Output: 999999999
    Explanation: We can use baskets 1 and 1000000000.
 

Constraints:
    n == position.length
    2 <= n <= 105
    1 <= position[i] <= 109
    All integers in position are distinct.
    2 <= m <= position.length
*/


#include <stdio.h>


void quick_sort_with_fixed_partition(int array[], int left, int right) {
    if (left >= right)
        return;
    
    int pivot_index = left + (right - left) / 2;
    int pivot_value = array[pivot_index];
    int t_left = left;
    int t_right = right;

    while (t_left <= t_right) {
        while (t_left <= right && array[t_left] < pivot_value) {
            t_left++;
        }
        while (t_right >= left && array[t_right] > pivot_value) {
            t_right--;
        }
        if (t_left <= t_right) {
            int temp = array[t_left];
            array[t_left] = array[t_right];
            array[t_right] = temp;
            t_left++;
            t_right--;
        }
    }

    if (left < t_right) {
        quick_sort_with_fixed_partition(array, left, t_right);
    }

    if (t_left < right) {
        quick_sort_with_fixed_partition(array, t_left, right);
    }
}


int is_valid_distance(int step_size, int* pos, int pos_size, int balls) {
    int pre_pos = pos[0];
    int placed = 1;

    for (int i = 0; i < pos_size; i++) {
        if (pos[i] - pre_pos >= step_size) {
            pre_pos = pos[i];
            placed++;
        }
    }

    return placed >= balls;
}


int max_distance(int* pos, int pos_size, int balls) {
    quick_sort_with_fixed_partition(pos, 0, pos_size - 1);

    int res = 0;
    int left = 1;
    int right = pos[pos_size - 1] - pos[0];

    while (left <= right) {
        int step_size = (left + right) / 2;

        if (is_valid_distance(step_size, pos, pos_size, balls)) {
            res = step_size;
            left = step_size + 1;
        } else {
            right = step_size - 1;
        }
    }

    return res;
}
