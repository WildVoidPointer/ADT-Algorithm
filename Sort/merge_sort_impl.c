#include "./array_utils/array_utils.h"

#include <stdio.h>


void merge_sort_merge_helper(
    int orig_arr[], int* copy_arr, int left, int mid, int right
) {
    for (int i = left; i <= right; i++) {
        copy_arr[i] = orig_arr[i];
    }
    
    int left_arr_idx = left; 
    int right_arr_idx = mid + 1;
    int orig_arr_idx = left;

    while ( 
        left_arr_idx <= mid && right_arr_idx <= right
    ) {
        if (copy_arr[left_arr_idx] <= copy_arr[right_arr_idx]) {
            orig_arr[orig_arr_idx++] = copy_arr[left_arr_idx++];
        } else {
            orig_arr[orig_arr_idx++] = copy_arr[right_arr_idx++];
        }
    }

    while (left_arr_idx <= mid) {
        orig_arr[orig_arr_idx++] = copy_arr[left_arr_idx++];
    }

    while (right_arr_idx <= right) {
        orig_arr[orig_arr_idx++] = copy_arr[right_arr_idx++];
    }
}


void merge_sort_with_self_recursion(int orig_arr[], int copy_arr[], int left, int right) {
    if (left < right) {
        int mid = (right + left) / 2;
        merge_sort_with_self_recursion(orig_arr, copy_arr, left, mid);
        merge_sort_with_self_recursion(orig_arr, copy_arr, mid + 1, right);
        merge_sort_merge_helper(orig_arr, copy_arr, left, mid, right);
    }
}


void merge_sort_with_self_iterable(int orig_arr[], int copy_arr[], int len) {

    if (len <= 1) {
        return;
    }

    int curr_size, left, right, mid;
    int left_idx, right_idx, copy_arr_idx;

    for (curr_size = 1; curr_size < len; curr_size *= 2) {

        for (left = 0; left < len - 1; left += 2 * curr_size) {

            mid = left + curr_size - 1;
            right = left + 2 * curr_size - 1;

            if (right > len - 1){
                right = len - 1;
            }

            left_idx = left; 
            right_idx = mid + 1;
            copy_arr_idx = left;

            while (left_idx <= mid && right_idx <= right) {
                if (orig_arr[left_idx] <= orig_arr[right_idx]) {
                    copy_arr[copy_arr_idx++] = orig_arr[left_idx++];
                } else {
                    copy_arr[copy_arr_idx++] = orig_arr[right_idx++];
                }
            }

            while (left_idx <= mid) {
                copy_arr[copy_arr_idx++] = orig_arr[left_idx++];
            }

            while (right_idx <= right) {
                copy_arr[copy_arr_idx++] = orig_arr[right_idx++];
            }

            for (int i = left; i < copy_arr_idx; i++) {
                orig_arr[i] = copy_arr[i];
            }
        }
    }
}


int main() {
    int test_array1[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len1 = sizeof(test_array1) / sizeof(test_array1[0]);
    int copy_arr[test_array_len1];
    merge_sort_with_self_recursion(test_array1, copy_arr, 0, test_array_len1 - 1);
    integer_array_println("SelfRecursionMergeSortedArray:  ", test_array1, test_array_len1);


    int test_array2[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len2 = sizeof(test_array2) / sizeof(test_array2[0]);
    merge_sort_with_self_iterable(test_array2, copy_arr, test_array_len2);
    integer_array_println(
        "SelfIterableMergeSortedArray:  ", test_array2, test_array_len2
    );

    return 0;
}
