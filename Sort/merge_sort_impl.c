#include "./array_utils/array_utils.h"

#include <stdio.h>


static void merge_sort_int_merge(
    int src_arr[], int copy_arr[], int left, int mid, int right
) {
    for (int i = left; i <= right; i++) {
        copy_arr[i] = src_arr[i];
    }
    
    int left_arr_idx = left; 
    int right_arr_idx = mid + 1;
    int src_arr_idx = left;
    
    while ( 
        left_arr_idx <= mid && right_arr_idx <= right
    ) {
        if (copy_arr[left_arr_idx] <= copy_arr[right_arr_idx]) {
            src_arr[src_arr_idx++] = copy_arr[left_arr_idx++];
        } else {
            src_arr[src_arr_idx++] = copy_arr[right_arr_idx++];
        }
    }

    while (left_arr_idx <= mid) {
        src_arr[src_arr_idx++] = copy_arr[left_arr_idx++];
    }

    while (right_arr_idx <= right) {
        src_arr[src_arr_idx++] = copy_arr[right_arr_idx++];
    }
}


static void merge_sort_int_recursion(
    int orig_arr[], int copy_arr[], int left, int right
) {
    if (left < right) {
        int mid = (right + left) / 2;
        merge_sort_int_recursion(orig_arr, copy_arr, left, mid);
        merge_sort_int_recursion(orig_arr, copy_arr, mid + 1, right);
        merge_sort_int_merge(orig_arr, copy_arr, left, mid, right);
    }
}


static void merge_sort_int_iteration(
    int src_arr[], int copy_arr[], int len
) {

    if (len <= 1) {
        return;
    }

    int curr_size, first_head, second_rear, pivot;
    int first_idx, second_idx, copy_arr_idx;

    for (curr_size = 1; curr_size < len; curr_size *= 2) {

        // 保证至少有一个数据可合并
        for (
            first_head = 0; 
            first_head < len - 1; 
            first_head += 2 * curr_size
        ) {

            pivot = first_head + curr_size - 1;

            // 确定第二个小数组结束位置
            second_rear = first_head + 2 * curr_size - 1;

            // 保证至少有一个数据可合并
            if (second_rear > len - 1) {
                second_rear = len - 1;
            }

            // 防止第一个数组越界
            if (pivot >= len - 1 || pivot < first_head) {
                continue;
            }

            // 在 copy 数组中开始合并
            first_idx = first_head; 
            second_idx = pivot + 1;
            copy_arr_idx = first_head;

            while (first_idx <= pivot && second_idx <= second_rear) {
                if (src_arr[first_idx] <= src_arr[second_idx]) {
                    copy_arr[copy_arr_idx++] = src_arr[first_idx++];
                } else {
                    copy_arr[copy_arr_idx++] = src_arr[second_idx++];
                }
            }

            while (first_idx <= pivot) {
                copy_arr[copy_arr_idx++] = src_arr[first_idx++];
            }

            while (second_idx <= second_rear) {
                copy_arr[copy_arr_idx++] = src_arr[second_idx++];
            }

            // 复制回原数组，以保证循环中处理有效
            for (int i = first_head; i < copy_arr_idx; i++) {
                src_arr[i] = copy_arr[i];
            }
        }
    }
}


int main() {

    int test_array1[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len1 = sizeof(test_array1) / sizeof(test_array1[0]);

    int copy_arr[test_array_len1];

    merge_sort_int_recursion(
        test_array1, 
        copy_arr, 
        0, 
        test_array_len1 - 1
    );

    integer_array_println(
        "SelfRecursionMergeSortedArray:  ", 
        test_array1, 
        test_array_len1
    );


    int test_array2[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len2 = sizeof(test_array2) / sizeof(test_array2[0]);
    merge_sort_int_iteration(test_array2, copy_arr, test_array_len2);
    integer_array_println(
        "SelfIterableMergeSortedArray:  ", test_array2, test_array_len2
    );

    return 0;
}
