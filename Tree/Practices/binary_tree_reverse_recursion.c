#include <stdio.h>
#include <stdlib.h>


typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


void binary_tree_reverse(TreeNode* root) {
    if (root != NULL) {
        TreeNode* tmp_node = root->left;
        root->left = root->right;
        root->right = tmp_node;
        
        binary_tree_reverse(root->left);
        binary_tree_reverse(root->right);
    }
}


TreeNode* binary_tree_node_create(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


// 生成 3 层满二叉树（节点顺序为 1, 2, 3, 4, 5, 6, 7 ）
TreeNode* default_full_binary_tree_generate() {
    // 创建根节点（第 1 层）
    TreeNode* root = binary_tree_node_create(1);
    
    // 创建第 2 层
    root->left = binary_tree_node_create(2);
    root->right = binary_tree_node_create(3);
    
    // 创建第 3 层
    root->left->left = binary_tree_node_create(4);
    root->left->right = binary_tree_node_create(5);
    root->right->left = binary_tree_node_create(6);
    root->right->right = binary_tree_node_create(7);
    
    return root;
}


void binary_tree_pre_order_print(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    binary_tree_pre_order_print(root->left);
    binary_tree_pre_order_print(root->right);
}


void binary_tree_destroy(TreeNode* root) {
    if (root == NULL) return;
    binary_tree_destroy(root->left);
    binary_tree_destroy(root->right);
    free(root);
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