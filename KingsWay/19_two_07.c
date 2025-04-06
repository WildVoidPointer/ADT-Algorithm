#include <stdio.h>


void array_section_elements_swap(int left, int right, int sl[]) {
    int mid = (left + right) / 2;
    for (int i = left; i <= mid; i++) {
        int t = sl[i];
        sl[i] = sl[right - i + left];
        sl[right - i + left] = t;
    }
}

void multi_seqlist_position_swap(int l1, int l2, int sl[]) {
    array_section_elements_swap(0, l1 + l2, sl);
    array_section_elements_swap(0, l2, sl);
    array_section_elements_swap(l2, l1 + l2, sl);
}



int main() {
    int arr[] = {1, 2, 3, 4, 1, 2, 3, 4, 5, 6, 7};
    multi_seqlist_position_swap(4, 7, arr);
    for (int i = 0; i < 11; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
}