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
    
    int arr[] = {1, 2, 3, 7, 6, 5};

    bubble_sort_without_sentry(arr, 6);
    bubble_sort_with_sentry(arr, 6);

    for (int i = 0; i < 6; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
    return 0;
}

