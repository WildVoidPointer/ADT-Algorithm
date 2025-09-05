#include <stdio.h>


void seqlist_reverse_in_space_o1(int len, int sl[len]) {
    int mid_idx = len / 2;
    
    for (int i = 0; i < mid_idx; i++) {
        int tmp = sl[i];
        sl[i] = sl[len - 1 - i];
        sl[len - 1 - i] = tmp;
    }
}


int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};

    seqlist_reverse_in_space_o1(7, arr);

    for (int i = 0; i < 7; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
}