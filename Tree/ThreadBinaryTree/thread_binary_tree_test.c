#include "thread_binary_tree.h"
#include "../BinaryTree/binary_tree.h"


int main() {
    BinaryTreeEleType tree_node_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int tree_node_array_len = 
        sizeof(tree_node_array) / sizeof(tree_node_array[0]);

    BinaryTree* bin_tree = BinaryTree_build_of_array(
        tree_node_array, tree_node_array_len
    );

    ThreadBinaryTree* built_th_tree = 
        ThreadBinaryTree_build_of_binary_tree(bin_tree);

    ThreadBinaryTree_threading(built_th_tree);


    ThreadBinaryTree_display(built_th_tree);


    ThreadBinaryTreeNode* threaded_root = ThreadBinaryTree_threaded_root(built_th_tree);

    ThreadBinaryTreeNode_display(threaded_root);
    
}
