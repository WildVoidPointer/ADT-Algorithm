#include "avl_tree.h"

#include <stdio.h>
#include <stdlib.h>


AvlTree* AvlTree_create() {
    AvlTree* tree = 
        (AvlTree*) malloc (sizeof(AvlTree));
    if (tree == NULL) {
        fprintf(stderr, AVL_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    tree->root = NULL;
    return tree;
}


int AvlTree_clean(AvlTree** balanced_tree) {
    if (balanced_tree == NULL || *balanced_tree == NULL) {
        fprintf(stderr, AVL_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    _AvlTree_clean_helper((*balanced_tree)->root);

    *balanced_tree = NULL;

    return 0;
}


int AvlTree_get_height(AvlTreeNode* balanced_node) {
    if (balanced_node == NULL) {
        fprintf(stderr, AVL_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    return balanced_node->height;
}


AvlTree* AvlTree_build_of_array(
    AvlTreeDataType arr[], int arr_len
) {
    if (arr == NULL || arr_len < 0) {
        fprintf(stderr, AVL_TREE_OTHER_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    AvlTree* balanced_tree = AvlTree_create();
    if (balanced_tree == NULL) {
        fprintf(stderr, AVL_TREE_BUILD_ERROR);
        return NULL;
    }

    for (int i = 0; i < arr_len; i++) {
        AvlTree_insert(balanced_tree, &arr[i]);
    }

    return balanced_tree;
}


int AvlTree_insert(
    AvlTree* balanced_tree, AvlTreeDataType* new_data
) {
    if (balanced_tree == NULL) {
        fprintf(stderr, AVL_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    if (new_data == NULL) {
        fprintf(stderr, AVL_TREE_OTHER_SRC_ACCESS_EXCEPTION);
        return -1;
    }

    AvlTreeNode* new_node = AvlTreeNode_create(new_data);
    if (new_node == NULL) {
        fprintf(stderr, AVL_TREE_INSERT_ERROR);
        return -1;
    }

    balanced_tree->root = 
        _AvlTree_insert_helper(balanced_tree->root, new_node);

    return 0;
}


int AvlTree_remove(
    AvlTree* balanced_tree, AvlTreeDataType* data
) {
    if (balanced_tree == NULL) {
        fprintf(stderr, AVL_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    if (data == NULL) {
        fprintf(stderr, AVL_TREE_OTHER_SRC_ACCESS_EXCEPTION);
        return -1;
    }

    balanced_tree->root = 
        _AvlTree_remove_helper(balanced_tree->root, data);

    return 0;
}


int AvlTree_in_order_println(AvlTree* balanced_tree) {
    if (balanced_tree == NULL) {
        fprintf(stderr, AVL_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    printf("AvlTree: {  ");
    _AvlTree_in_order_traversal(balanced_tree->root);
    printf("}\n");
    return 0;
}


int AvlTree_update_height(AvlTreeNode* adjust_node) {
    if (adjust_node == NULL) {
        fprintf(stderr, AVL_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    int left_height = adjust_node->left == NULL ? 
        0 : AvlTree_get_height(adjust_node->left);

    int right_height = adjust_node->right == NULL ? 
        0 : AvlTree_get_height(adjust_node->right);

    adjust_node->height = (left_height > right_height ? left_height : right_height) + 1;

    return 0;
}


int AvlTree_get_balance_factor(AvlTreeNode* balanced_node) {
    if (balanced_node == NULL) {
        fprintf(stderr, AVL_TREE_NODE_ACCESS_EXCEPTION);
        return 0;
    }

    
    int left_height = balanced_node->left == NULL ? 
        0 : AvlTree_get_height(balanced_node->left);

    int right_height = balanced_node->right == NULL ? 
        0 : AvlTree_get_height(balanced_node->right);

    return left_height - right_height;
}


AvlTreeNode*
AvlTree_right_rotate(AvlTreeNode* balanced_node) {

    if (balanced_node == NULL) {
        fprintf(stderr, AVL_TREE_NODE_ACCESS_EXCEPTION);
        return NULL;
    }

    AvlTreeNode* left_node = balanced_node->left;
    AvlTreeNode* left_node_right_subtree = left_node->right;

    left_node->right = balanced_node;
    balanced_node->left = left_node_right_subtree;
    
    AvlTree_update_height(balanced_node);
    AvlTree_update_height(left_node);

    return left_node;
}


AvlTreeNode* 
AvlTree_left_rotate(AvlTreeNode* balanced_node) {

    if (balanced_node == NULL) {
        fprintf(stderr, AVL_TREE_NODE_ACCESS_EXCEPTION);
        return NULL;
    }

    AvlTreeNode* right_node = balanced_node->right;
    AvlTreeNode* right_node_left_subtree = right_node->left;

    right_node->left = balanced_node;
    balanced_node->right = right_node_left_subtree;

    AvlTree_update_height(balanced_node);
    AvlTree_update_height(right_node);

    return right_node;
}


AvlTreeNode* _AvlTree_insert_helper(
    AvlTreeNode* balanced_node, AvlTreeNode* new_node
) {
    if (new_node == NULL) {
        fprintf(stderr, AVL_TREE_NODE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    if (balanced_node == NULL) {
        return new_node;
    }

    if (new_node->data == balanced_node->data) {

        fprintf(stderr, AVL_TREE_INSERT_EXCEPTION);
        AvlTreeNode_clean(&new_node);
        return balanced_node;

    } else if (new_node->data < balanced_node->data) {

        balanced_node->left = _AvlTree_insert_helper(
            balanced_node->left, new_node
        );

    } else if (new_node->data > balanced_node->data) {

        balanced_node->right = _AvlTree_insert_helper(
            balanced_node->right, new_node
        );

    }

    AvlTree_update_height(balanced_node);

    int balance_factor = AvlTree_get_balance_factor(balanced_node);

    // 左左情况
    if (balance_factor > 1 
        && AvlTree_get_balance_factor(balanced_node->left) >= 0
    ) {
        return AvlTree_right_rotate(balanced_node);
    }
    
    // 左右情况
    if (balance_factor > 1 
        && AvlTree_get_balance_factor(balanced_node->left) < 0
    ) {
        balanced_node->left = AvlTree_left_rotate(balanced_node->left);
        return AvlTree_right_rotate(balanced_node);
    }
    
    // 右右情况
    if (balance_factor < -1 
        && AvlTree_get_balance_factor(balanced_node->right) <= 0
    ) {
        return AvlTree_left_rotate(balanced_node);
    }
    
    // 右左情况
    if (balance_factor < -1 
        && AvlTree_get_balance_factor(balanced_node->right) > 0
    ) {
        balanced_node->right = AvlTree_right_rotate(balanced_node->right);
        return AvlTree_left_rotate(balanced_node);
    }

    return balanced_node;
}


AvlTreeNode* _AvlTree_remove_helper(
    AvlTreeNode* balanced_node, AvlTreeDataType* data
) {
    if (balanced_node == NULL) {
        return balanced_node;
    }

    if (*data < balanced_node->data) {

        balanced_node->left = 
            _AvlTree_remove_helper(balanced_node->left, data);

    } else if (*data > balanced_node->data) {

        balanced_node->right = 
            _AvlTree_remove_helper(balanced_node->right, data);

    } else {
        // 找到要删除的节点
        if (balanced_node->left == NULL || balanced_node->right == NULL) {

            AvlTreeNode* temp = 
                balanced_node->right == NULL ? 
                balanced_node->left : balanced_node->right;

            AvlTreeNode_clean(&balanced_node);

            balanced_node = temp;
            
        } else {
            // 有两个子节点情况
            AvlTreeNode* successor = balanced_node->right;
            while (successor->left != NULL) {
                successor = successor->left;
            }
            
            balanced_node->data = successor->data;
            balanced_node->right = _AvlTree_remove_helper(
                balanced_node->right, &successor->data);
        }
    }

    if (balanced_node == NULL) {
        return balanced_node;
    }

    // 更新高度并重新平衡
    AvlTree_update_height(balanced_node);
    int balance_factor = AvlTree_get_balance_factor(balanced_node);

    // 左左情况
    if (balance_factor > 1 
        && AvlTree_get_balance_factor(balanced_node->left) >= 0
    ) {
        return AvlTree_right_rotate(balanced_node);
    }
    
    // 左右情况
    if (balance_factor > 1 
        && AvlTree_get_balance_factor(balanced_node->left) < 0
    ) {
        balanced_node->left = AvlTree_left_rotate(balanced_node->left);
        return AvlTree_right_rotate(balanced_node);
    }
    
    // 右右情况
    if (balance_factor < -1 
        && AvlTree_get_balance_factor(balanced_node->right) <= 0
    ) {
        return AvlTree_left_rotate(balanced_node);
    }
    
    // 右左情况
    if (balance_factor < -1 
        && AvlTree_get_balance_factor(balanced_node->right) > 0
    ) {
        balanced_node->right = AvlTree_right_rotate(balanced_node->right);
        return AvlTree_left_rotate(balanced_node);
    }

    return balanced_node;
}


void _AvlTree_clean_helper(AvlTreeNode* balanced_node) {
    if (balanced_node != NULL) {
        _AvlTree_clean_helper(balanced_node->left);
        _AvlTree_clean_helper(balanced_node->right);
        AvlTreeNode_clean(&balanced_node);
    }
}


void _AvlTree_in_order_traversal(AvlTreeNode* balanced_node) {
    if (balanced_node != NULL) {
        _AvlTree_in_order_traversal(balanced_node->left);
        printf("%d  ", balanced_node->data);
        _AvlTree_in_order_traversal(balanced_node->right);
    }
}



AvlTreeNode* 
AvlTreeNode_create(AvlTreeDataType* data) {
    if (data == NULL) {
        fprintf(stderr, AVL_TREE_NODE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    AvlTreeNode* new_node = 
        (AvlTreeNode*) malloc (sizeof(AvlTreeNode));

    if (new_node == NULL) {
        fprintf(stderr, AVL_TREE_NODE_CREATE_ERROR);
        return NULL;
    }

    new_node->left = new_node->right = NULL;
    new_node->data = *data;
    new_node->height = 1;

    return new_node;
}


int AvlTreeNode_clean(AvlTreeNode** balanced_node) { 
    if (balanced_node == NULL || (*balanced_node) == NULL) {
        fprintf(stderr, AVL_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    free(*balanced_node);
    *balanced_node = NULL;

    return 0;
}
