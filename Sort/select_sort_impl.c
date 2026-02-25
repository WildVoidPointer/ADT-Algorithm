#include "./array_utils/array_utils.h"

#include <stdio.h>


void select_sort(int array[], int len) {
    int min_val_index, tmp_swap_buf;

    for (int i = 0; i < len; i++) {
        min_val_index = i;

        for (int j = i + 1; j < len; j++) {
            if (array[min_val_index] > array[j]) {
                min_val_index = j;
            }
        }

        if (min_val_index != i) {
            tmp_swap_buf = array[i];
            array[i] = array[min_val_index];
            array[min_val_index] = tmp_swap_buf;
        }
    }
}


int main() {

    int test_array[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len = sizeof(test_array) / sizeof(test_array[0]);

    select_sort(test_array, test_array_len);

    integer_array_println(
        "SelectSortedArray:  ", 
        test_array, 
        test_array_len
    );
    
    return 0;
}
