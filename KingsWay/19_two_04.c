#include <stdio.h>


void remove_range_values(int seqlist[], int size, int buttom, int top, int fill) {
    int index = 0;

    if (buttom > top || size <= 0) {
        printf("error\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (seqlist[i] >= buttom && seqlist[i] <= top) {
            seqlist[i] = fill;
        } else {
            seqlist[index++] = seqlist[i];
        }
    }

    for (int i = index; i < size; i++) {
        seqlist[i] = fill;
    }
}


int main() {
    int size = 8;
    int seqlist[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    remove_range_values(seqlist, size, 3, 6, -1);

    for (int i = 0; i < size; i++) {
        printf("%d  ", seqlist[i]);
    }
    puts("");
    return 0;
}
