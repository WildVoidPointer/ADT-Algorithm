#include "binary_tree.h"


int main() {
    BinaryTreeEleType arr[] = {1, 2, 3, -1, 4, 5, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    BinaryTreeEleType pre_order[] = {1, 2, -1, 4, 3, 5, 6};

    BinaryTreeEleType in_order[] = {-1, 2, 4, 1, 5, 3, 6};

    BinaryTreeEleType post_order[] = {-1, 4, 2, 5, 6, 3, 1};
    
    BinaryTree* tree = BinaryTree_build_of_array(arr, size);
    BinaryTree_display(tree, NULL);

    BinaryTree_display(tree, BinaryTree_pre_order_traversal);

    BinaryTree_display(tree, BinaryTree_in_order_traversal);

    BinaryTree_display(tree, BinaryTree_post_order_traversal);

    BinaryTree* pre_order_build_res = 
        BinaryTree_build_of_pre_order(in_order, pre_order, size, size);

    BinaryTree* post_order_build_res = 
        BinaryTree_build_of_post_order(in_order, post_order, size, size);

    BinaryTree_display(pre_order_build_res, NULL);

    BinaryTree_clean(&pre_order_build_res);

    BinaryTree_display(post_order_build_res, NULL);

    BinaryTree_clean(&post_order_build_res);

    BinaryTree_clean(&tree);

    return 0;
}
