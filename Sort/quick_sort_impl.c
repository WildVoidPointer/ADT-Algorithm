#include "./array_utils/array_utils.h"

#include <stdio.h>


void quick_sort_with_fixed_partition(
    int array[], int left_index, int right_index
) {

    if (left_index >= right_index) 
        return;
    
    int pivot_index = (left_index + right_index) / 2;
    int pivot_val = array[pivot_index];

    int tmp_left = left_index;
    int tmp_right = right_index;

    while (tmp_left <= tmp_right) {
        while (array[tmp_left] < pivot_val) {
            tmp_left++;
        }

        while (array[tmp_right] > pivot_val) {
            tmp_right--;
        }

        if (tmp_left <= tmp_right) {
            int tmp_left_val = array[tmp_left];
            array[tmp_left] = array[tmp_right];
            array[tmp_right] = tmp_left_val;

            tmp_left++;
            tmp_right--;
        }
    }

    quick_sort_with_fixed_partition(array, left_index, tmp_right);
    quick_sort_with_fixed_partition(array, tmp_left, right_index);
}


int quick_sort_first_partition_helper(
    int array[], int left_index, int right_index
) {
    int pivot_val = array[left_index];

    while (left_index < right_index && array[right_index] > pivot_val) {
        right_index--;
    }
    array[left_index] = array[right_index];

    while (left_index < right_index && array[left_index] < pivot_val) {
        left_index++;
    }
    array[right_index] = array[left_index];

    array[left_index] = pivot_val;
    return left_index;
}


void quick_sort_with_first_partition(
    int array[], int left_index, int right_index
) {
    if (left_index < right_index) {
        
        int pivot_index = quick_sort_first_partition_helper(
            array, 
            left_index, 
            right_index
        );

        quick_sort_with_first_partition(array, pivot_index + 1, right_index);
        quick_sort_with_first_partition(array, left_index, pivot_index - 1);
    }
}


int main() {
    
    int test_array1[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len1 = sizeof(test_array1) / sizeof(test_array1[0]);
    quick_sort_with_fixed_partition(test_array1, 0, test_array_len1 - 1);
    integer_array_println(
        "FixedPartitionQuickSoredArray:  ", test_array1, test_array_len1
    );


    int test_array2[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len2 = sizeof(test_array2) / sizeof(test_array2[0]);
    quick_sort_with_first_partition(test_array2, 0, test_array_len2 - 1);
    integer_array_println(
        "FirstPartitionQuickSoredArray:  ", test_array2, test_array_len2
    );


    return 0;
}

