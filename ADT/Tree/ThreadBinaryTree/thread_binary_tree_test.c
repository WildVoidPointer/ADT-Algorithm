#include "thread_binary_tree.h"
#include "../BinaryTree/binary_tree.h"


int main() {
    BinaryTreeDataType tree_node_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int tree_node_array_len = 
        sizeof(tree_node_array) / sizeof(tree_node_array[0]);



    BinaryTree* bin_tree = BinaryTree_build_of_array(
        tree_node_array, tree_node_array_len
    );
    ThreadBinaryTree* built_th_tree = 
        ThreadBinaryTree_build_of_binary_tree(bin_tree);

    printf("ThreadBinaryTreeBuildResultOfBinaryTree\n");
    ThreadBinaryTree_display(
        built_th_tree, ThreadBinaryTree_pre_order_traverse
    );
    ThreadBinaryTree_display(
        built_th_tree, ThreadBinaryTree_in_order_traverse
    );
    ThreadBinaryTree_display(
        built_th_tree, ThreadBinaryTree_post_order_traverse
    );
    ThreadBinaryTree_destroy(&built_th_tree);
    printf("ThreadBinaryTreeCleanResult: %p\n", built_th_tree);
    printf("====================\n");



    ThreadBinaryTree* pre_order_thread_tree = 
        ThreadBinaryTree_build_of_binary_tree(bin_tree);

    printf("ThreadBinaryTreePreOrderThreadResult\n");
    ThreadBinaryTree_threading(
        pre_order_thread_tree, ThreadBinaryTree_pre_order_traverse
    );
    ThreadBinaryTree_display(
        pre_order_thread_tree, ThreadBinaryTree_pre_order_threaded_traverse
    );
    ThreadBinaryTree_destroy(&pre_order_thread_tree);
    printf("====================\n");


        
    ThreadBinaryTree* in_order_thread_tree = 
        ThreadBinaryTree_build_of_binary_tree(bin_tree);
    
    printf("ThreadBinaryTreeInOrderThreadResult\n");
    ThreadBinaryTree_threading(
        in_order_thread_tree, ThreadBinaryTree_in_order_traverse
    );
    ThreadBinaryTree_display(
        in_order_thread_tree, ThreadBinaryTree_in_order_threaded_traverse
    );
    ThreadBinaryTree_destroy(&in_order_thread_tree);
    printf("====================\n");



    ThreadBinaryTree* post_order_thread_tree =
        ThreadBinaryTree_build_of_binary_tree(bin_tree);
    printf("ThreadBinaryTreePostOrderThreadResult\n");
    ThreadBinaryTree_threading(
        post_order_thread_tree, ThreadBinaryTree_post_order_traverse
    );
    
}  