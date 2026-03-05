#include "./array_utils/array_utils.h"
#include <stdio.h>


static void quick_sort_int_hoare(
    int array[], int left, int right
) {

    if (left >= right) 
        return;
    
    int pivot = (left + right) / 2;
    int pivot_val = array[pivot];

    int curr_left = left;
    int curr_right = right;

    while (curr_left <= curr_right) {

        while (
            curr_left < right 
            && array[curr_left] < pivot_val
        ) {
            curr_left++;
        }

        while (
            curr_right > left 
            && array[curr_right] > pivot_val
        ) {
            curr_right--;
        }

        if (curr_left <= curr_right) {
            int tmp_left_val = array[curr_left];
            array[curr_left] = array[curr_right];
            array[curr_right] = tmp_left_val;

            curr_left++;
            curr_right--;
        }
    }

    quick_sort_int_hoare(array, left, curr_right);
    quick_sort_int_hoare(array, curr_left, right);
}


static int quick_sort_int_lomuto_partition(
    int array[], int left, int right
) {
    int pivot_val = array[left];

    while (left < right && array[right] > pivot_val) {
        right--;
    }

    array[left] = array[right];

    while (left < right && array[left] < pivot_val) {
        left++;
    }

    array[right] = array[left];

    array[left] = pivot_val;

    return left;
}


static void quick_sort_int_lomuto(
    int array[], int left, int right
) {
    if (left < right) {
        
        int pivot = quick_sort_int_lomuto_partition(
            array, 
            left, 
            right
        );

        quick_sort_int_lomuto(array, pivot + 1, right);
        quick_sort_int_lomuto(array, left, pivot - 1);
    }
}


int main() {
    
    int test_array1[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len1 = sizeof(test_array1) / sizeof(test_array1[0]);

    quick_sort_int_hoare(test_array1, 0, test_array_len1 - 1);

    integer_array_println(
        "FixedPartitionQuickSoredArray:  ", 
        test_array1, 
        test_array_len1
    );


    int test_array2[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len2 = sizeof(test_array2) / sizeof(test_array2[0]);

    quick_sort_int_lomuto(test_array2, 0, test_array_len2 - 1);

    integer_array_println(
        "FirstPartitionQuickSoredArray:  ", 
        test_array2, 
        test_array_len2
    );


    return 0;
}

