#include <stdio.h>


static void int_swap(int arr[], int left, int right) {

    int tmp = arr[left];

    arr[left] = arr[right];

    arr[right] = tmp;

}


static int quick_select_lomuto_iteration(
    int arr[], int left, int right, int k
) {

    if (left == right) {
        return arr[left];
    }
    
    int pivot_val = arr[right];
    
    int offset = left;

    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot_val) {
            int_swap(arr, offset, i);
            offset++;
        }
    }
    
    int_swap(arr, offset, right);
    
    if (offset == k - 1) {
        return arr[offset];
    } 
    else if (offset > k - 1) {
        return quick_select_lomuto_iteration(arr, left, offset - 1, k);
    } 
    else {
        return quick_select_lomuto_iteration(arr, offset + 1, right, k);
    }

}


static int quick_select_lomuto_partition(int arr[], int left, int right) {
    
    if (left == right) {
        return left;
    }

    int pivot_val = arr[right];

    int offset = left;

    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot_val) {
            int_swap(arr, offset, i);
            offset++;
        }
    }

    // offset 最终会指向序列中大于 pivot_val 的第一个位置

    int_swap(arr, offset, right);

    return offset;
}


static int quick_select_lomuto_recursion(
    int arr[], int left, int right, int k
) {

    if (left == right) {
        return arr[left];
    }

    int pivot = quick_select_lomuto_partition(arr, left, right);

    if (pivot == k - 1) {

        return arr[pivot];

    } else if (pivot < k - 1) {

        return quick_select_lomuto_recursion(arr, pivot + 1, right, k);

    } else {

        return quick_select_lomuto_recursion(arr, left, pivot - 1, k);
    }
}


static void entry() {

    int arr_len = 0;

    int k = 0;

    scanf("%d %d", &arr_len, &k);

    int arr[arr_len];

    for (int i = 0; i < arr_len; i++) {
        scanf("%d", &arr[i]);
    }

    int k_val = quick_select_lomuto_iteration(arr, 0, arr_len - 1, k);

    printf("%d", k_val);

}


int main() {
    entry();
}
