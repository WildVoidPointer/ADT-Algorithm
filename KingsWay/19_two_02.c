#include <stdio.h>


void seqlist_reverse_in_o1(int length, int seqlist[length]) {
    int mid = length / 2;
    for (int i = 0; i < mid; i++) {
        int tmp = seqlist[i];
        seqlist[i] = seqlist[length - 1 - i];
        seqlist[length - 1 - i] = tmp;
    }
}


int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};

    seqlist_reverse_in_o1(6, arr);

    for (int i = 0; i < 6; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
}