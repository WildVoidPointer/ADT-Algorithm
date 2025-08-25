#include "thread_binary_tree.h"
#include "../BinaryTree/binary_tree.h"


int linked_print_handle(
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandleContext* th_ctx
) {
    printf("%d  ", th_node->data);
}


int main() {
    BinaryTreeEleType tree_node_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int tree_node_array_len = 
        sizeof(tree_node_array) / sizeof(tree_node_array[0]);

    BinaryTree* bin_tree = BinaryTree_build_of_array(
        tree_node_array, tree_node_array_len
    );

    ThreadBinaryTree* th_tree = 
        ThreadBinaryTree_build_of_binary_tree(bin_tree);

    ThreadBinaryTree_threading(th_tree);

    ThreadBinaryTree_linked_traversal(th_tree->root, linked_print_handle, NULL);
    putc('\n', stdout);
}
