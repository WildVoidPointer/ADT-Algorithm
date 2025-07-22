#include <stdio.h>


void search_swap_specific_element(int target, int size, int sl[]) {
    int left = 0;
    int right = size;
    int is_found = 0;
    int t_pos;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        t_pos = mid;
        if (sl[mid] == target) {
            is_found = 1;
            break;
        }
        else if (sl[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (is_found && t_pos != size - 1) {
        int t = sl[t_pos];
        sl[t_pos] = sl[t_pos + 1];
        sl[t_pos + 1] = t;
    } 
    else if (!is_found) {
        for (int i = size; i > t_pos; i--) {
            sl[i] = sl[i - 1];
        }
        sl[t_pos] = target;
    }
}


int main() {

    int arr[22] = {1, 3, 4, 5, 6, 7, 10};
    int size = 7;
    search_swap_specific_element(10, size, arr);
    for (int i = 0; i < size + 1; i++) {
        printf("%d  ", arr[i]);
    }
    putc('\n', stderr);
}