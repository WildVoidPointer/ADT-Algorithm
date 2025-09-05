#include <stdio.h>


int 
sl_min_ele_rm_and_trailing_ele_fill(int len, int sl[]) {
    if (len == 0) {
        puts("error");
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

    int res = sl_min_ele_rm_and_trailing_ele_fill(6, arr);

    for (int i = 0; i < 6; i++) {
        printf("%d  ", arr[i]);
    }
    puts("");
}