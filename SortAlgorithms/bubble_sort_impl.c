#include <stdio.h>

void bubble_sort(int array[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int _t = array[j];
                array[j] = array[j + 1];
                array[j + 1] = _t;
            }
        }
    }
}


int main(int argc, char const *argv[])
{
    int arr[] = {5, 4, 3, 1, 2, 0};
    bubble_sort(arr, 6);
    for (int i = 0; i < 6; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
    return 0;
}

