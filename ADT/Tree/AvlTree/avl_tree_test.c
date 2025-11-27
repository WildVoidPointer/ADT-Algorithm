#include "avl_tree.h"

#include <stdio.h>


int main() {
    AvlTreeDataType arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int arr_len = sizeof(arr) / sizeof(arr[0]);
    AvlTreeDataType to_delete = 7;

    AvlTree* balanced_tree = AvlTree_build_of_array(
        arr, arr_len
    );

    if (balanced_tree ==  NULL) {
        return -1;
    }

    AvlTree_in_order_println(balanced_tree);

    AvlTree_remove(balanced_tree, &to_delete);

    AvlTree_in_order_println(balanced_tree);

    AvlTree_destroy(&balanced_tree);

    return 0;
}