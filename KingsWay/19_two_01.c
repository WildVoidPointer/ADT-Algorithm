#include <stdio.h>


int 
seqlist_ele_remove_and_tail_fill(int length, int seqlist[length]) {
    if (length == 0) {
        puts("error");
    }

    int min_index = 0;
    for (int i = 1; i < length; i++) {
        if (seqlist[min_index] > seqlist[i]) {
            min_index = i;
        }
    }

    int min_element = seqlist[min_index];
    seqlist[min_index] = seqlist[length - 1];
    return min_element;    
}


int main() {
    int arr[] = {1, 2, 3, 4, 0, 6};

    int res = seqlist_ele_remove_and_tail_fill(6, arr);

    for (int i = 0; i < 6; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
}