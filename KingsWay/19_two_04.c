#include <stdio.h>


void sl_remove_range_values(int sl[], int size, int buttom, int top, int fill) {
    int index = 0;

    if (buttom > top || size <= 0) {
        printf("error\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (sl[i] >= buttom && sl[i] <= top) {
            sl[i] = fill;
        } else {
            sl[index++] = sl[i];
        }
    }

    for (int i = index; i < size; i++) {
        sl[i] = fill;
    }
}


int main() {
    int size = 8;
    int seqlist[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    sl_remove_range_values(seqlist, size, 3, 6, -1);

    for (int i = 0; i < size; i++) {
        printf("%d  ", seqlist[i]);
    }
    puts("");
    return 0;
}
