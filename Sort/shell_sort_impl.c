#include "./array_utils/array_utils.h"

#include <stdio.h>


void shell_sort(int* array, int len) {
    int key, offset;
    int gap = len / 2;

    while (gap > 0) {

        for (int i = gap; i < len; i++) {
            key = array[i];
            offset = i;

            while (offset >= gap && array[offset - gap] > key) {
                array[offset] = array[offset - gap];
                offset = offset - gap;
            }

            array[offset] = key;
        }

        gap = gap / 2;
    }
}


int main() {

    int test_array[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};

    int test_array_len = sizeof(test_array) / sizeof(test_array[0]);

    shell_sort(test_array, test_array_len);

    integer_array_println(
        "ShellSortedArray:  ", 
        test_array, 
        test_array_len
    );
    
    return 0;
}
