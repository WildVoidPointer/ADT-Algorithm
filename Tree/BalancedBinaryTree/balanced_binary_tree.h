#ifndef BALANCED_BINARY_TREE_H_
#define BALANCED_BINARY_TREE_H_


#include <stdio.h>
#include <stdlib.h>


#define BALANCED_BINARY_TREE_CREATE_ERROR \
    "BalancedBinaryTreeCreateError: " \
    "Memory initialization of BalancedBinaryTree failed\n"


#define BALANCED_BINARY_TREE_BUILD_ERROR \
    "BalancedBinaryTreeBuildError: " \
    "Memory initialization failed in process of building BalancedBinaryTree\n"


#define BALANCED_BINARY_TREE_INSERT_ERROR \
    "BalancedBinaryTreeInsertError: " \
    "Memory initialization failed in process of inserting BalancedBinaryTree\n"


#define BALANCED_BINARY_TREE_INSERT_EXCEPTION \
    "BalancedBinaryTreeInsertException: " \
    "The insert BalancedBinaryTreeData is exists\n"


#define BALANCED_BINARY_TREE_ACCESS_EXCEPTION \
    "BalancedBinaryTreeAccessException: " \
    "The data address of the BalancedBinaryTree cannot be accessed\n"


#define BALANCED_BINARY_TREE_OTHER_SRC_ACCESS_EXCEPTION \
    "BalancedBinaryTreeOtherSrcAccessException: " \
    "The data address of the search target cannot be accessed\n"
    


// the exception messages of BalancedBinaryTreeNode options
#define BALANCED_BINARY_TREE_NODE_CREATE_ERROR \
    "BalancedBinaryTreeNodeCreateError: " \
    "Memory initialization of BalancedBinaryTreeNode failed\n"


#define BALANCED_BINARY_TREE_NODE_ACCESS_EXCEPTION \
    "BalancedBinaryTreeNodeAccessException: " \
    "The data address of the BalancedBinaryTreeNode cannot be accessed\n"


#define BALANCED_BINARY_TREE_NODE_SRC_ACCESS_EXCEPTION \
    "BalancedBinaryTreeNodeSrcAccessException: " \
    "The data address of the BalancedBinaryTreeNode data cannot be accessed\n"


typedef int BalancedBinaryTreeDataType;


typedef struct BalancedBinaryTreeNode {
    BalancedBinaryTreeDataType data;
    struct BalancedBinaryTreeNode* left;
    struct BalancedBinaryTreeNode* right;
    int height;
} BalancedBinaryTreeNode;


typedef struct BalancedBinaryTree {
    BalancedBinaryTreeNode* root;
} BalancedBinaryTree;


BalancedBinaryTree* BalancedBinaryTree_create();


int BalancedBinaryTree_clean(BalancedBinaryTree** balanced_tree);


int BalancedBinaryTree_get_height(BalancedBinaryTreeNode* balanced_node);


BalancedBinaryTree* BalancedBinaryTree_build_of_array(
    BalancedBinaryTreeDataType arr[], int arr_len
);


int BalancedBinaryTree_insert(
    BalancedBinaryTree* balanced_tree, BalancedBinaryTreeDataType* new_data
);


int BalancedBinaryTree_remove(
    BalancedBinaryTree* balanced_tree, BalancedBinaryTreeDataType* new_data
);


int BalancedBinaryTree_in_order_println(BalancedBinaryTree* balanced_tree);


int BalancedBinaryTree_update_height(BalancedBinaryTreeNode* adjust_node);


int BalancedBinaryTree_get_balance_factor(BalancedBinaryTreeNode* balanced_node);


BalancedBinaryTreeNode* 
BalancedBinaryTree_right_rorate(BalancedBinaryTreeNode* balanced_node);


BalancedBinaryTreeNode* 
BalancedBinaryTree_left_rorate(BalancedBinaryTreeNode* balanced_node);


BalancedBinaryTreeNode* _BalancedBinaryTree_insert_helper(
    BalancedBinaryTreeNode* balanced_node, BalancedBinaryTreeNode* new_node
);


void _BalancedBinaryTree_in_order_traversal();


int _BalancedBinaryTree_remove_helper(
    BalancedBinaryTreeNode* balanced_node, BalancedBinaryTreeDataType* new_data
);



BalancedBinaryTreeNode* 
BalancedBinaryTreeNode_create(BalancedBinaryTreeDataType* data);


int BalancedBinaryTreeNode_clean(BalancedBinaryTreeNode** balanced_node);


#endif 
