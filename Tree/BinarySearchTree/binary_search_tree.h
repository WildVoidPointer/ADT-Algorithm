#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_


#include <stdio.h>
#include <stdlib.h>


#define BINARY_SEARCH_TREE_CREATE_ERROR \
    "BinarySearchTreeCreateError: " \
    "Memory initialization of BinarySearchTree failed\n"


#define BINARY_SEARCH_TREE_BUILD_ERROR \
    "BinarySearchTreeBuildError: " \
    "Memory initialization failed in process of building BinarySearchTree\n"


#define BINARY_SEARCH_TREE_INSERT_ERROR \
    "BinarySearchTreeInsertError: " \
    "Memory initialization failed in process of inserting BinarySearchTree\n"


#define BINARY_SEARCH_TREE_INSERT_EXCEPTION \
    "BinarySearchTreeInsertException: " \
    "The insert BinarySearchTreeData is exists\n"


#define BINARY_SEARCH_TREE_ACCESS_EXCEPTION \
    "BinarySearchTreeAccessException: " \
    "The data address of the BinarySearchTree cannot be accessed\n"


#define BINARY_SEARCH_TREE_SEARCH_TARGET_ACCESS_EXCEPTION \
    "BinarySearchTreeSearchTargetAccessException: " \
    "The data address of the search target cannot be accessed\n"


#define BINARY_SEARCH_TREE_INSERT_TARGET_ACCESS_EXCEPTION \
    "BinarySearchTreeInsertTargetAccessException: " \
    "The data address of the insert target cannot be accessed\n"


// the exception messages of BinarySearchTreeNode options
#define BINARY_SEARCH_TREE_NODE_CREATE_ERROR \
    "BinarySearchTreeNodeCreateError: " \
    "Memory initialization of BinarySearchTreeNode failed\n"


#define BINARY_SEARCH_TREE_NODE_ACCESS_EXCEPTION \
    "BinarySearchTreeNodeAccessException: " \
    "The data address of the BinarySearchTreeNode cannot be accessed\n"


#define BINARY_SEARCH_TREE_NODE_SRC_ACCESS_EXCEPTION \
    "BinarySearchTreeNodeSrcAccessException: " \
    "The data address of the BinarySearchTreeNode data cannot be accessed\n"


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
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_key
);


int BinarySearchTree_insert(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
);


int BinarySearchTree_remove(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
);



BinarySearchTreeNode* 
BinarySearchTreeNode_create(BinarySearchTreeDataType* bst_data);


int BinarySearchTreeNode_clean(BinarySearchTree** bst_node);

#endif // BINARY_SEARCH_TREE_H_
