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


int BalancedBinaryTree_clean(BalancedBinaryTree** balanced_tree);


int BalancedBinaryTree_get_height(BalancedBinaryTreeNode* balanced_node) {
    if (balanced_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    return balanced_node->height;
}


BalancedBinaryTree* BalancedBinaryTree_build_of_array(
    BalancedBinaryTreeDataType arr[], int arr_len
);


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

    _BalancedBinaryTree_insert_helper(balanced_tree->root, new_node);

    return 0;
}


int BalancedBinaryTree_remove(
    BalancedBinaryTree* balanced_tree, BalancedBinaryTreeDataType* new_data
);


BalancedBinaryTreeNode*
BalancedBinaryTree_right_rorate(BalancedBinaryTreeNode* balanced_node) {

    if (balanced_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    BalancedBinaryTreeNode* left = balanced_node->left;
    BalancedBinaryTreeNode* left_right_subtree = left->right;

    left->right = balanced_node;
    balanced_node = left_right_subtree;
    
    left->height = 
        BalancedBinaryTree_get_height(left->left->height) 
            > BalancedBinaryTree_get_height(left->right->height) ? 
            left->left->height : left->right->height;
    
    balanced_node->height = 
        BalancedBinaryTree_get_height(balanced_node->left->height) 
            > BalancedBinaryTree_get_height(balanced_node->right->height) ? 
            balanced_node->left->height : balanced_node->right->height;
    
    return left;
}


BalancedBinaryTreeNode* 
BalancedBinaryTree_left_rorate(BalancedBinaryTreeNode* balanced_node) {

    if (balanced_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    BalancedBinaryTreeNode* right = balanced_node->right;
    BalancedBinaryTreeNode* right_left_subtree = right->left;

    right->left = balanced_node;
    balanced_node->right = right_left_subtree;

    right->height = 
        BalancedBinaryTree_get_height(right->left->height) 
            > BalancedBinaryTree_get_height(right->right->height) ? 
            right->left->height : right->right->height;

    balanced_node->height = 
        BalancedBinaryTree_get_height(balanced_node->left->height) 
            > BalancedBinaryTree_get_height(balanced_node->right->height) ? 
            balanced_node->left->height : balanced_node->right->height;

    return right;
}


BalancedBinaryTreeNode* _BalancedBinaryTree_insert_helper(
    BalancedBinaryTreeNode* balanced_node, BalancedBinaryTreeNode* new_node
) {
    if (new_node == NULL) {
        fprintf(stderr, BALANCED_BINARY_TREE_NODE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    if (new_node == NULL) {
        return new_node;
    }

    if (new_node->data < balanced_node->data) {
        balanced_node = _BalancedBinaryTree_insert_helper(
            balanced_node->left, new_node
        );
    } else if (new_node->data > balanced_node->data) {
        balanced_node = _BalancedBinaryTree_insert_helper(
            balanced_node->right, new_node
        );
    }
}


int _BalancedBinaryTree_remove_helper(
    BalancedBinaryTreeNode* balanced_node, BalancedBinaryTreeDataType* new_data
);



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
