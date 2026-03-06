#include <stdio.h>


typedef long long int llint_t;

static llint_t violence_enumeration(int arr[], int len) {

    llint_t count = 0;

    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] > arr[j]) {
                count++;
            }
        }
    }

    return count;
}


static llint_t divide_rule(int arr[], int copied[], int len) {

    llint_t count = 0;

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

                if (arr[first_idx] <= arr[second_idx]) {
                    copied[copied_idx++] = arr[first_idx++];
                } else {
                    copied[copied_idx++] = arr[second_idx++];
                    /* 
                     利用归并操作在分割子数组递归时逐渐返回时的有序性保证
                     此时若 first_idx 值大于 second_idx 处的值，则序列
                     first 中 first_idx 之前的值都小于 second_idx 处值
                     */
                    count += pivot - first_idx + 1;
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

    return count;
}


static void entry() {

    int len = 0;

    scanf("%d", &len);

    int arr[len], copied[len];

    for (int i = 0; i < len; i++) {
        scanf("%d", &arr[i]);
    }

    llint_t res = divide_rule(arr, copied, len);

    printf("%lld", res);
}


int main() {
    entry();
}
