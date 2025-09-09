#include "binary_search_tree.h"

#include <stdio.h>
#include <stdlib.h>


BinarySearchTree* BinarySearchTree_create() {
    BinarySearchTree* bs_tree = 
        (BinarySearchTree*) malloc (sizeof(BinarySearchTree));
    if (bs_tree == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_CREATE_ERROR);
        return NULL;
    }

    bs_tree->root = NULL;
    return bs_tree;
}


int BinarySearchTree_clean(BinarySearchTree** bs_tree);


BinarySearchTree* BinarySearchTree_build_of_array(
    BinarySearchTreeDataType arr[], int len
);


BinarySearchTreeNode* BinarySearchTree_search(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_key
) {
    if (bs_tree == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    if (bst_key == NULL) {
        fprintf(
            stderr, 
            BINARY_SEARCH_TREE_SEARCH_TARGET_ACCESS_EXCEPTION
        );
        return NULL;
    }

    BinarySearchTreeNode* curr = bs_tree->root;
    while (curr != NULL && *bst_key != curr->data) {
        if (*bst_key > curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return curr;
}


int BinarySearchTree_insert(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
) {
    if (bs_tree == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    if (bst_data == NULL) {
        fprintf(
            stderr, 
            BINARY_SEARCH_TREE_INSERT_TARGET_ACCESS_EXCEPTION
        );
        return -1;
    }

    if (bs_tree->root == NULL) {
        BinarySearchTreeNode* bst_root = BinarySearchTreeNode_create(bst_data);
        if (bst_root == NULL) {
            fprintf(stderr, BINARY_SEARCH_TREE_INSERT_ERROR);
            return -1;
        }

        bs_tree->root = bst_root;
        return 0;
    } else if (bst_data == bs_tree) {
        
    }
}


int BinarySearchTree_remove(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
);


BinarySearchTreeNode* 
BinarySearchTreeNode_create(BinarySearchTreeDataType* bst_data) {
    if (bst_data == NULL) {
        fprintf(
            stderr,
            BINARY_SEARCH_TREE_NODE_SRC_ACCESS_EXCEPTION
        );
        return NULL;
    }

    BinarySearchTreeNode* bst_node = 
        (BinarySearchTreeNode*) malloc (sizeof(BinarySearchTreeNode));
    if (bst_node == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_NODE_CREATE_ERROR);
        return NULL;
    }

    bst_node->data = *bst_data;
    bst_node->left = bst_node->right = NULL;
    return bst_node;
}


int BinarySearchTreeNode_clean(BinarySearchTree** bst_node) {
    if (bst_node == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    free(*bst_node);
    *bst_node = NULL;
    return 0;
}
