#include <stdio.h>


int seqlist_remove_range_values(
    int sl[], int len, int buttom, int top, int fill
) {
    int index = 0;

    if (buttom > top) {
        printf("error: the range of s and t is invalid\n");
        return len;
    }

    if (len <= 0) {
        puts("error: the seqlist is empty\n");
        return len;
    }

    for (int i = 0; i < len; i++) {
        if (buttom <= sl[i] && sl[i] <= top) {
            sl[i] = fill;
        } else {
            sl[index++] = sl[i];
        }
    }

    // If time complexity is not taken into account, 
    // the elements in the remaining positions can be cleared

    for (int i = index; i < len; i++) {
        sl[i] = fill;
    }

    return index;
}


int main() {
    int size = 8;
    int seqlist[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    int new_len = seqlist_remove_range_values(seqlist, size, 3, 6, -1);

    for (int i = 0; i < new_len; i++) {
        printf("%d  ", seqlist[i]);
    }
    puts("");
    return 0;
}
