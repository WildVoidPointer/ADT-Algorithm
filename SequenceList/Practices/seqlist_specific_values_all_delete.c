#include <stdio.h>


int seqlist_specific_vals_delete(
    int len, int sl[], int target, int fill
) {

    int index = 0;

    for (int i = 0; i < len; i++) {
        if (target == sl[i]) {
            sl[i] = fill;
        } else {
            sl[index++] = sl[i];
        }
    }

    return index;
}


int main() {
    int arr[] = {1, 2, 2, 2, 5, 2};

    int new_length = seqlist_specific_vals_delete(6, arr, 2, -1);

    for (int i = 0; i < new_length; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
}