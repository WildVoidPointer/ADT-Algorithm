#include <stdio.h>


void sl_specific_eles_cleaner(
    int len, int sl[], int target, int fill) {

    int index = 0;
    for (int i = 0; i < len; i++) {
        if (sl[i] == target) {
            sl[i] = fill;
        } else {
            sl[index] = sl[i];
            index++;
        }
    }

    // During normal exams, we don’t need to fill in the elements 
    // of the residual positions. We can directly modify the length
    // of the sequence list.
    for (int i = index; i < len; i++) {
        sl[i] = fill;
    }
}


int main() {
    int arr[] = {1, 2, 2, 2, 5, 2};

    sl_specific_eles_cleaner(6, arr, 2, -1);

    for (int i = 0; i < 6; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
}