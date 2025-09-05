#include <stdio.h>


int seqlist_minimum_del_and_last_fill(int len, int sl[]) {
    if (len <= 0) {
        puts("error: the sequence_list is empty\n");
    }

    int min_index = 0;
    for (int i = 1; i < len; i++) {
        if (sl[min_index] > sl[i]) {
            min_index = i;
        }
    }

    int min_element = sl[min_index];
    sl[min_index] = sl[len - 1];
    return min_element;    
}


int main() {
    int arr[] = {1, 2, 3, 4, 0, 6};

    int res = seqlist_minimum_del_and_last_fill(6, arr);

    for (int i = 0; i < 6; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
}