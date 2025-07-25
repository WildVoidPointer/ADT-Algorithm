#include "binary_tree.h"


int main() {
    BinaryTreeEleType arr[] = {1, 2, 3, -1, 4, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    BinaryTree* tree = BinaryTree_build_of_array(arr, size);
    BinaryTree_display(tree, NULL);

    BinaryTree_display(tree, BinaryTree_pre_order_traversal);

    BinaryTree_display(tree, BinaryTree_in_order_traversal);

    BinaryTree_display(tree, BinaryTree_post_order_traversal);

    BinaryTree_clean(&tree);

    return 0;
}
