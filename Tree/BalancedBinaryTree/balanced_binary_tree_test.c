#include "balanced_binary_tree.h"

#include <stdio.h>


int main() {
    BalancedBinaryTreeDataType arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int arr_len = sizeof(arr) / sizeof(arr[0]);

    BalancedBinaryTree* balanced_tree = BalancedBinaryTree_build_of_array(
        arr, 2
    );

    if (balanced_tree ==  NULL) {
        return -1;
    }

    BalancedBinaryTree_in_order_println(balanced_tree);

    BalancedBinaryTree_clean(&balanced_tree);

    return 0;
}