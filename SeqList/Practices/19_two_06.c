#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* multi_seqlist_collect(int first, int sl1[first], int second, int sl2[second]) {
    int* collect_res = malloc((first + second) * sizeof(int));
    memcpy(collect_res, sl1, first * sizeof(int));
    for (int i = 0, index = first; i < second; i++, index++) {
        collect_res[index] = sl2[i];
    }
    // memcpy((char*)collect_res + first, sl2, second);
    return collect_res;
}


int main() {
    int size = 5;
    int sl1[5] = {1, 2, 3, 4, 5};
    int sl2[5] = {1, 2, 3, 4, 5};
    int* res =  multi_seqlist_collect(size, sl1, size, sl2);
    for (int i = 0; i < 2 * size; i++) {
        printf("%d  ", res[i]);
    }

    free(res);
}