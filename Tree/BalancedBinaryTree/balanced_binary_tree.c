#include "balanced_binary_tree.h"

#include <stdio.h>
#include <stdlib.h>


BalancedBinaryTree* BalancedBinaryTree_create() {
    BalancedBinaryTree* tree = 
        (BalancedBinaryTree*) malloc (sizeof(BalancedBinaryTree));
    if (tree == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    tree->root = NULL;
    return tree;
}


int BalancedBinaryTree_clean(BalancedBinaryTree** balanced_tree) {
    if (balanced_tree == NULL || *balanced_tree == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    _BalancedBinaryTree_clean_helper((*balanced_tree)->root);

    *balanced_tree = NULL;

    return 0;
}


int BalancedBinaryTree_get_height(BalancedBinaryTreeNode* balanced_node) {
    if (balanced_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    return balanced_node->height;
}


BalancedBinaryTree* BalancedBinaryTree_build_of_array(
    BalancedBinaryTreeDataType arr[], int arr_len
) {
    if (arr == NULL || arr_len < 0) {
        fprintf(stderr, BALANCED_BINARY_TREE_OTHER_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    BalancedBinaryTree* balanced_tree = BalancedBinaryTree_create();
    if (balanced_tree == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_BUILD_ERROR);
        return NULL;
    }

    for (int i = 0; i < arr_len; i++) {
        BalancedBinaryTree_insert(balanced_tree, &arr[i]);
    }

    return balanced_tree;
}


int BalancedBinaryTree_insert(
    BalancedBinaryTree* balanced_tree, BalancedBinaryTreeDataType* new_data
) {
    if (balanced_tree == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    if (new_data == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_OTHER_SRC_ACCESS_EXCEPTION);
        return -1;
    }

    BalancedBinaryTreeNode* new_node = BalancedBinaryTreeNode_create(new_data);
    if (new_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_INSERT_ERROR);
        return -1;
    }

    balanced_tree->root = 
        _BalancedBinaryTree_insert_helper(balanced_tree->root, new_node);

    return 0;
}


int BalancedBinaryTree_remove(
    BalancedBinaryTree* balanced_tree, BalancedBinaryTreeDataType* data
) {
    if (balanced_tree == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    if (data == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_OTHER_SRC_ACCESS_EXCEPTION);
        return -1;
    }

    balanced_tree->root = 
        _BalancedBinaryTree_remove_helper(balanced_tree->root, data);

    return 0;
}


int BalancedBinaryTree_in_order_println(BalancedBinaryTree* balanced_tree) {
    if (balanced_tree == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    printf("BalancedBinaryTree: {  ");
    _BalancedBinaryTree_in_order_traversal(balanced_tree->root);
    printf("}\n");
    return 0;
}


int BalancedBinaryTree_update_height(BalancedBinaryTreeNode* adjust_node) {
    if (adjust_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    int left_height = adjust_node->left == NULL ? 
        0 : BalancedBinaryTree_get_height(adjust_node->left);

    int right_height = adjust_node->right == NULL ? 
        0 : BalancedBinaryTree_get_height(adjust_node->right);

    adjust_node->height = (left_height > right_height ? left_height : right_height) + 1;

    return 0;
}


int BalancedBinaryTree_get_balance_factor(BalancedBinaryTreeNode* balanced_node) {
    if (balanced_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return 0;
    }

    
    int left_height = balanced_node->left == NULL ? 
        0 : BalancedBinaryTree_get_height(balanced_node->left);

    int right_height = balanced_node->right == NULL ? 
        0 : BalancedBinaryTree_get_height(balanced_node->right);

    return left_height - right_height;
}


BalancedBinaryTreeNode*
BalancedBinaryTree_right_rotate(BalancedBinaryTreeNode* balanced_node) {

    if (balanced_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return NULL;
    }

    BalancedBinaryTreeNode* left_node = balanced_node->left;
    BalancedBinaryTreeNode* left_node_right_subtree = left_node->right;

    left_node->right = balanced_node;
    balanced_node->left = left_node_right_subtree;
    
    BalancedBinaryTree_update_height(balanced_node);
    BalancedBinaryTree_update_height(left_node);

    return left_node;
}


BalancedBinaryTreeNode* 
BalancedBinaryTree_left_rotate(BalancedBinaryTreeNode* balanced_node) {

    if (balanced_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return NULL;
    }

    BalancedBinaryTreeNode* right_node = balanced_node->right;
    BalancedBinaryTreeNode* right_node_left_subtree = right_node->left;

    right_node->left = balanced_node;
    balanced_node->right = right_node_left_subtree;

    BalancedBinaryTree_update_height(balanced_node);
    BalancedBinaryTree_update_height(right_node);

    return right_node;
}


BalancedBinaryTreeNode* _BalancedBinaryTree_insert_helper(
    BalancedBinaryTreeNode* balanced_node, BalancedBinaryTreeNode* new_node
) {
    if (new_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    if (balanced_node == NULL) {
        return new_node;
    }

    if (new_node->data == balanced_node->data) {

        fprintf(stderr, BALANCED_BINARY_TREE_INSERT_EXCEPTION);
        BalancedBinaryTreeNode_clean(&new_node);
        return balanced_node;

    } else if (new_node->data < balanced_node->data) {

        balanced_node->left = _BalancedBinaryTree_insert_helper(
            balanced_node->left, new_node
        );

    } else if (new_node->data > balanced_node->data) {

        balanced_node->right = _BalancedBinaryTree_insert_helper(
            balanced_node->right, new_node
        );

    }

    BalancedBinaryTree_update_height(balanced_node);

    int balance_factor = BalancedBinaryTree_get_balance_factor(balanced_node);

    // 左左情况
    if (balance_factor > 1 
        && BalancedBinaryTree_get_balance_factor(balanced_node->left) >= 0
    ) {
        return BalancedBinaryTree_right_rotate(balanced_node);
    }
    
    // 左右情况
    if (balance_factor > 1 
        && BalancedBinaryTree_get_balance_factor(balanced_node->left) < 0
    ) {
        balanced_node->left = BalancedBinaryTree_left_rotate(balanced_node->left);
        return BalancedBinaryTree_right_rotate(balanced_node);
    }
    
    // 右右情况
    if (balance_factor < -1 
        && BalancedBinaryTree_get_balance_factor(balanced_node->right) <= 0
    ) {
        return BalancedBinaryTree_left_rotate(balanced_node);
    }
    
    // 右左情况
    if (balance_factor < -1 
        && BalancedBinaryTree_get_balance_factor(balanced_node->right) > 0
    ) {
        balanced_node->right = BalancedBinaryTree_right_rotate(balanced_node->right);
        return BalancedBinaryTree_left_rotate(balanced_node);
    }

    return balanced_node;
}


BalancedBinaryTreeNode* _BalancedBinaryTree_remove_helper(
    BalancedBinaryTreeNode* balanced_node, BalancedBinaryTreeDataType* data
) {
    if (balanced_node == NULL) {
        return balanced_node;
    }

    if (*data < balanced_node->data) {

        balanced_node->left = 
            _BalancedBinaryTree_remove_helper(balanced_node->left, data);

    } else if (*data > balanced_node->data) {

        balanced_node->right = 
            _BalancedBinaryTree_remove_helper(balanced_node->right, data);

    } else {
        // 找到要删除的节点
        if (balanced_node->left == NULL || balanced_node->right == NULL) {

            BalancedBinaryTreeNode* temp = 
                balanced_node->right == NULL ? 
                balanced_node->left : balanced_node->right;

            BalancedBinaryTreeNode_clean(&balanced_node);

            balanced_node = temp;
            
        } else {
            // 有两个子节点情况
            BalancedBinaryTreeNode* successor = balanced_node->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }
            
            balanced_node->data = successor->data;
            balanced_node->right = _BalancedBinaryTree_remove_helper(
                balanced_node->right, &successor->data);
        }
    }

    if (balanced_node == NULL) {
        return balanced_node;
    }

    // 更新高度并重新平衡
    BalancedBinaryTree_update_height(balanced_node);
    int balance_factor = BalancedBinaryTree_get_balance_factor(balanced_node);

    // 左左情况
    if (balance_factor > 1 
        && BalancedBinaryTree_get_balance_factor(balanced_node->left) >= 0
    ) {
        return BalancedBinaryTree_right_rotate(balanced_node);
    }
    
    // 左右情况
    if (balance_factor > 1 
        && BalancedBinaryTree_get_balance_factor(balanced_node->left) < 0
    ) {
        balanced_node->left = BalancedBinaryTree_left_rotate(balanced_node->left);
        return BalancedBinaryTree_right_rotate(balanced_node);
    }
    
    // 右右情况
    if (balance_factor < -1 
        && BalancedBinaryTree_get_balance_factor(balanced_node->right) <= 0
    ) {
        return BalancedBinaryTree_left_rotate(balanced_node);
    }
    
    // 右左情况
    if (balance_factor < -1 
        && BalancedBinaryTree_get_balance_factor(balanced_node->right) > 0
    ) {
        balanced_node->right = BalancedBinaryTree_right_rotate(balanced_node->right);
        return BalancedBinaryTree_left_rotate(balanced_node);
    }

    return balanced_node;
}


void _BalancedBinaryTree_clean_helper(BalancedBinaryTreeNode* balanced_node) {
    if (balanced_node != NULL) {
        _BalancedBinaryTree_clean_helper(balanced_node->left);
        _BalancedBinaryTree_clean_helper(balanced_node->right);
        BalancedBinaryTreeNode_clean(&balanced_node);
    }
}


void _BalancedBinaryTree_in_order_traversal(BalancedBinaryTreeNode* balanced_node) {
    if (balanced_node != NULL) {
        _BalancedBinaryTree_in_order_traversal(balanced_node->left);
        printf("%d  ", balanced_node->data);
        _BalancedBinaryTree_in_order_traversal(balanced_node->right);
    }
}



BalancedBinaryTreeNode* 
BalancedBinaryTreeNode_create(BalancedBinaryTreeDataType* data) {
    if (data == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    BalancedBinaryTreeNode* new_node = 
        (BalancedBinaryTreeNode*) malloc (sizeof(BalancedBinaryTreeNode));

    if (new_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_CREATE_ERROR);
        return NULL;
    }

    new_node->left = new_node->right = NULL;
    new_node->data = *data;
    new_node->height = 1;

    return new_node;
}


int BalancedBinaryTreeNode_clean(BalancedBinaryTreeNode** balanced_node) { 
    if (balanced_node == NULL || (*balanced_node) == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    free(*balanced_node);
    *balanced_node = NULL;

    return 0;
}
