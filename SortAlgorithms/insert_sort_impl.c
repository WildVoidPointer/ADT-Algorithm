#include <stdio.h>
#include "./array_utils/array_utils.h"


void insert_sort_without_sentry(int array[], int len) {
    int key, offset;
    for (int i = 1; i < len; i++) {
        key = array[i];
        offset = i - 1;
        while (offset >= 0 && key < array[offset]) {
            array[offset + 1] = array[offset];
            offset--;
        }
        array[offset + 1] = key;
    }
}


void insert_sort_half_interval(int array[], int len) {
    int key;
    int high, low, mid;

    for (int i = 1; i < len; i++) {
        key = array[i];
        low = 0;
        high = i - 1;

        while (low <= high) {
            mid = (high + low) / 2;
            if (key < array[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        for (int j = i -1; j >= high + 1; j--) {
            array[j + 1] = array[j];
        }

        array[high + 1] = key;
    }
}


int main() {
    int test_array1[] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    int test_array_len1 = sizeof(test_array1) / sizeof(test_array1[0]);
    insert_sort_without_sentry(test_array1, test_array_len1);
    integer_array_println(
        "NoSentrySortedArray:  ", test_array1, test_array_len1
    );

    int test_array2[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len2 = sizeof(test_array2) / sizeof(test_array2[0]);
    insert_sort_half_interval(test_array2, test_array_len2);
    integer_array_println(
        "HalfINtervalSortedArray:  ", test_array2, test_array_len2
    );


    return 0;
}
