#include <stdio.h>

void remove_recuring_elements(int size, int seqlist[size], int fill) {
    int index = 1;
    int buf = seqlist[0];

    for (int i = 1; i < size; i++) {
        if (seqlist[i] == buf) {
            seqlist[i] = fill;
        } else {
            buf = seqlist[i];
            seqlist[index++] = seqlist[i];
        }
    }

    for (int i = index; i < size; i++) {
        seqlist[i] = fill;
    }
}


int main() {
    int size = 8;
    int seqlist[8] = {1, 2, 2, 3, 3, 5, 5, 8};

    remove_recuring_elements(size, seqlist, -1);

    for (int i = 0; i < size; i++) {
        printf("%d  ", seqlist[i]);
    }
    puts("");
    return 0;
}
