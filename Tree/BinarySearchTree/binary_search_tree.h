#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_


#include <stdio.h>
#include <stdlib.h>


typedef int BinarySearchTreeDataType;


typedef struct BinarySearchTreeNode {
    BinarySearchTreeDataType data;
    struct BinarySearchTreeNode* left;
    struct BinarySearchTreeNode* right;
} BinarySearchTreeNode;


typedef struct BinarySearchTree {
    BinarySearchTreeNode* root;
} BinarySearchTree;


BinarySearchTree* BinarySearchTree_create();


int BinarySearchTree_clean(BinarySearchTree** bs_tree);


BinarySearchTree* BinarySearchTree_build_of_array(
    BinarySearchTreeDataType arr[], int len
);


BinarySearchTreeNode* BinarySearchTree_search(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
);


int BinarySearchTree_insert(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
);


int BinarySearchTree_remove(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
);

#endif // BINARY_SEARCH_TREE_H_
