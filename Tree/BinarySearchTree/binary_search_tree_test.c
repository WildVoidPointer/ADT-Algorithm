#include "binary_search_tree.h"


#include <stdio.h>
#include <stdlib.h>


void binary_tree_in_order_print(BinarySearchTreeNode* root) {
    if (root != NULL) {
        binary_tree_in_order_print(root->left);
        printf("%d  ", root->data);
        binary_tree_in_order_print(root->right);
    }
}


void binary_tree_in_order_println(BinarySearchTree* bs_tree) {
    binary_tree_in_order_print(bs_tree->root);
    printf("\n");
}


int main() {
    int test_array1[] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    int test_array_len1 = sizeof(test_array1) / sizeof(test_array1[0]);

    BinarySearchTree* built_bst = BinarySearchTree_build_of_array(
        test_array1, test_array_len1
    );

    binary_tree_in_order_println(built_bst);

    int wait_delete = 4;
    BinarySearchTree_remove(built_bst, &wait_delete);
    binary_tree_in_order_println(built_bst);


    BinarySearchTree_clean(&built_bst);
}

