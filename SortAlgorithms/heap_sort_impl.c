#include "./array_utils/array_utils.h"

#include <stdio.h>


void heap_sort_heap_adjust(int arr[], int start, int end) {
    int key = arr[start];
    for (int j = 2 * start; j <= end; j = j * 2) {

        if (j < end && arr[j] < arr[j + 1]) {
            j++;
        }

        if (key >= arr[j]) {
            break;
        } else {
            arr[start] = arr[j];
            start = j;
        }
    }

    arr[start] = key;
}


void heap_sort(int arr[], int len) {
    // 初始建堆过程
    for (int i = len / 2; i >= 0; i--) {
        heap_sort_heap_adjust(arr, i, len - 1);
    }

    // 逐步调整子堆
    int tmp;
    for (int i = len - 1; i > 0; i--) {
        tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;
        heap_sort_heap_adjust(arr, 0, i - 1);
    }
}


int main() {
    int test_array[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len = sizeof(test_array) / sizeof(test_array[0]);
    heap_sort(test_array, test_array_len);
    integer_array_println(
        "HeapSortedReasult: ", test_array, test_array_len
    );

    return 0;
}
