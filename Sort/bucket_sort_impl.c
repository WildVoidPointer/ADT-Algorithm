#include <stdio.h>
#include <string.h>


void bucket_sort(int array[], int len, int record_buf_size) {
    int record_buf[record_buf_size];
    memset(record_buf, 0, sizeof(record_buf));

    for (int i = 0; i < len; i++) {
        record_buf[array[i]]++;
    }

    for (int i = 0; i < record_buf_size; i++) {
        for (int j = 0; j < record_buf[i]; j++) {
            printf("%d ", i);
        }
    }
    puts("");
}


int main(int argc, char const *argv[]) {
    
    int arr[6] = {2, 2, 3, 3, 1, 0};
    bucket_sort(arr, 6, 20);

    return 0;
}

