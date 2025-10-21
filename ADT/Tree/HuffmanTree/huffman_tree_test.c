#include "huffman_tree.h"


void merge_for_integer_array_merge_sort(
    int orig_arr[], int copy_arr[], int left, int mid, int right
) {
    for (int i = left; i <= right; i++) {
        copy_arr[i] = orig_arr[i];
    }

    int orig_arr_idx = left;
    int left_idx = left;
    int right_idx = mid + 1;

    while (left_idx <= mid && right_idx <= right) {
        if (copy_arr[left_idx] <= copy_arr[right_idx]) {
            orig_arr[orig_arr_idx++] = copy_arr[left_idx++];
        } else {
            orig_arr[orig_arr_idx++] = copy_arr[right_idx++];
        }
    }

    while (left_idx <= mid) {
        orig_arr[orig_arr_idx++] = copy_arr[left_idx++];
    }

    while (right_idx <= right) {
        orig_arr[orig_arr_idx++] = copy_arr[right_idx++];
    }
}


void integer_array_merge_sort(int orig_arr[], int copy_arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        integer_array_merge_sort(orig_arr, copy_arr, left, mid);
        integer_array_merge_sort(orig_arr, copy_arr, mid + 1, right);
        merge_for_integer_array_merge_sort(orig_arr, copy_arr, left, mid, right);
    }
}


void integer_array_println(char* desp, int array[], int len) {
    fputs(desp, stdout);
    for (int i = 0; i < len; i++) {
        printf("%d  ", array[i]);
    }
    putc('\n', stdout);
}


int main() {
    HuffmanTreeDataType test_arr[] = {5, 9, 12, 13, 16, 45};
    int test_arr_len = sizeof(test_arr) / sizeof(test_arr[0]);
    HuffmanTreeDataType buf_arr[test_arr_len];
    integer_array_merge_sort(test_arr, buf_arr, 0, test_arr_len - 1);
    integer_array_println("MergeSortedResult: ", test_arr, test_arr_len);


    HuffmanTree* empty_hf_tree = HuffmanTree_create();
    HuffmanTree_display(empty_hf_tree);
    HuffmanTree_clean(&empty_hf_tree);
    printf("HuffmanTreeCleanReasult: %p\n", empty_hf_tree);


    HuffmanTree* build_from_array = HuffmanTree_build_of_any_array(
        test_arr, test_arr_len
    );
    HuffmanTree_display(build_from_array);
    HuffmanTree_clean(&build_from_array);

    return 0;
}
