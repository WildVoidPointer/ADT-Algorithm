#include <stdio.h>


static void merge_sort(int arr[], int copied[], int len) {

    if (len < 1) {
        return;
    }

    for (int curr_size = 1; curr_size < len; curr_size *= 2) {

        for (
            int first_head = 0; 
            first_head < len - 1; 
            first_head += 2 * curr_size
        ) {

            int pivot = first_head + curr_size - 1;

            int second_rear = first_head + 2 * curr_size - 1;

            if (second_rear > len - 1) {
                second_rear = len - 1;
            }

            if (pivot >= len - 1 || pivot < first_head) {
                continue;
            }

            int first_idx = first_head;

            int second_idx = pivot + 1;

            int copied_idx = first_head;

            while (first_idx <= pivot && second_idx <= second_rear) {

                if (arr[first_idx] < arr[second_idx]) {
                    copied[copied_idx++] = arr[first_idx++];
                } else {
                    copied[copied_idx++] = arr[second_idx++];
                }
            }

            while (first_idx <= pivot) {
                copied[copied_idx++] = arr[first_idx++];
            }

            while (second_idx <= second_rear) {
                copied[copied_idx++] = arr[second_idx++];
            }

            for (int i = first_head; i < copied_idx; i++) {
                arr[i] = copied[i];
            }

        }
    }
}


static void integers_println(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}


static void entry() {

    int len = 0;

    scanf("%d", &len);

    int arr[len], copied[len];

    for (int i = 0; i < len; i++) {
        scanf("%d", &arr[i]);
    }


    merge_sort(arr, copied, len);

    integers_println(copied, len);

}


int main() {
    entry();
}
