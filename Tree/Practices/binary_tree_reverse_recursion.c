#include "tree_utils/tree_utils.h"


#include <stdio.h>
#include <stdlib.h>


void binary_tree_reverse(TreeNode* root) {
    if (root != NULL) {
        TreeNode* tmp_node = root->left;
        root->left = root->right;
        root->right = tmp_node;
        
        binary_tree_reverse(root->left);
        binary_tree_reverse(root->right);
    }
}



int main() {
    
    TreeNode* root = default_full_binary_tree_generate();

    binary_tree_pre_order_print(root); // 未翻转前预期输出： 1 2 4 5 3 6 7
    putc('\n', stdout);

    binary_tree_reverse(root);
    binary_tree_pre_order_print(root); // 翻转后预期输出： 1 3 7 6 2 5 4
    putc('\n', stdout);
    
    return 0;
}
