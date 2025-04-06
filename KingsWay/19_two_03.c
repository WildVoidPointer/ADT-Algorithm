#include <stdio.h>


void specific_eles_cleaner(
    int length, int seqlist[length], int target, int fill) {

    int index = 0;
    for (int i = 0; i < length; i++) {
        if (seqlist[i] == target) {
            seqlist[i] = fill;
        } else {
            seqlist[index] = seqlist[i];
            index++;
        }
    }

    for (int i = index; i < length; i++) {
        seqlist[i] = fill;
    }
}


int main() {
    int arr[] = {1, 2, 2, 2, 5, 2};

    specific_eles_cleaner(6, arr, 2, -1);

    for (int i = 0; i < 6; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
}