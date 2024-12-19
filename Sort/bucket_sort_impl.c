#include <stdio.h>


#define MAX_LENGTH 100


void bucket_sort(int array[], int len) {
    int _record_array[MAX_LENGTH] = {0};
    for (int i = 0; i < len; i++) {
        _record_array[array[i]]++;
    }

    for (int i = 0; i < MAX_LENGTH; i++) {
        for (int j = 0; j < _record_array[i]; j++) {
            printf("%d ", i);
        }
        
    }
    puts("");
}


int main(int argc, char const *argv[]) {
    int arr[6] = {2, 2, 3, 3, 1, 0};
    bucket_sort(arr, 6);
    return 0;
}

