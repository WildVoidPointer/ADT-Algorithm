#include "./array_utils/array_utils.h"

#include <stdio.h>


void bubble_sort_without_sentry(int array[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}


void bubble_sort_with_sentry(int array[], int len) {
    int is_not_swapped = 1;

    for (int i = 0; i < len - 1; i++) {

        for (int j = 0; j < len - i - 1; j++) {

            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                is_not_swapped = 0;
            }
        }

        if (is_not_swapped) {
            break;
        }

        is_not_swapped = 1;
    }
}


int main(int argc, char const *argv[]) {
    
    int test_array1[] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    int test_array_len1 = sizeof(test_array1) / sizeof(test_array1[0]);
    bubble_sort_without_sentry(test_array1, test_array_len1);
    integer_array_println("NoSentrySortedArray:  ", test_array1, test_array_len1);


    int test_array2[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len2 = sizeof(test_array2) / sizeof(test_array2[0]);
    bubble_sort_with_sentry(test_array2, test_array_len2);
    integer_array_println("SentrySortedArray:  ", test_array2, test_array_len2);

    
    return 0;
}

