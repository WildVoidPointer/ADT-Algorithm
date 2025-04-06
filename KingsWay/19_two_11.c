#include <stdio.h>


int search_multi_seqs_median1(int sl1[], int sl2[], int len) {
    int i = 0, j = 0, index = 0;
    int temp[2 * len];

    while (i < len && j < len) {
        if (sl1[i] < sl2[j]) {
            temp[index++] = sl1[i++];
        }
        else if (sl1[i] > sl2[j]) {
            temp[index++] = sl2[j++];
        }
        else {
            temp[index++] = sl1[i++];
            temp[index++] = sl2[j++];
        }
    }

    if (i < len) {
        for (int k = i; k < len; k++) {
            temp[index++] = sl1[k];
        }
    }
    if (j < len) {
        for (int k = j; k < len; k++) {
            temp[index++] = sl2[k];
        }
    }

    return (temp[len - 1] + temp[len]) / 2;
}


int search_multi_seqs_median2(int sl1[], int sl2[], int len) {
    int i = 0, j = 0, count = 0;
    int prev = 0, curr = 0;

    while (count <= len) {
        prev = curr;

        if (i < len && sl1[i] < sl2[j]) {
            curr = sl1[i++];
        }
        else if (j < len && sl2[j] <= sl1[i]) {
            curr = sl2[j++];
        }

        count++;
    }

    return (prev + curr) / 2;

}




int main() {
    int sl1[] = {11, 13, 15, 17, 19};
    int sl2[] = {2, 4, 6, 8, 20};
    int len = 5;
    
    printf(
        "%d\n",
        search_multi_seqs_median2(sl1, sl2, len)
    );
}