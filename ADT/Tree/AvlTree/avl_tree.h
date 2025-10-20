#ifndef AVL_TREE_H_
#define avl_TREE_H_


#include <stdio.h>
#include <stdlib.h>


#define AVL_TREE_CREATE_ERROR \
    "AvlTreeCreateError: " \
    "Memory initialization of AvlTree failed\n"


#define AVL_TREE_BUILD_ERROR \
    "AvlTreeBuildError: " \
    "Memory initialization failed in process of building AvlTree\n"


#define AVL_TREE_INSERT_ERROR \
    "AvlTreeInsertError: " \
    "Memory initialization failed in process of inserting AvlTree\n"


#define AVL_TREE_INSERT_EXCEPTION \
    "AvlTreeInsertException: " \
    "The insert AvlTreeData is exists\n"


#define AVL_TREE_ACCESS_EXCEPTION \
    "AvlTreeAccessException: " \
    "The data address of the AvlTree cannot be accessed\n"


#define AVL_TREE_OTHER_SRC_ACCESS_EXCEPTION \
    "AvlTreeOtherSrcAccessException: " \
    "The data address of the search target cannot be accessed\n"
    


// the exception messages of AvlTreeNode options
#define AVL_TREE_NODE_CREATE_ERROR \
    "AvlTreeNodeCreateError: " \
    "Memory initialization of AvlTreeNode failed\n"


#define AVL_TREE_NODE_ACCESS_EXCEPTION \
    "AvlTreeNodeAccessException: " \
    "The data address of the AvlTreeNode cannot be accessed\n"


#define AVL_TREE_NODE_SRC_ACCESS_EXCEPTION \
    "AvlTreeNodeSrcAccessException: " \
    "The data address of the AvlTreeNode data cannot be accessed\n"


typedef int AvlTreeDataType;


typedef struct AvlTreeNode {
    AvlTreeDataType data;
    struct AvlTreeNode* left;
    struct AvlTreeNode* right;
    int height;
} AvlTreeNode;


typedef struct AvlTree {
    AvlTreeNode* root;
} AvlTree;


AvlTree* AvlTree_create();


int AvlTree_clean(AvlTree** balanced_tree);


int AvlTree_get_height(AvlTreeNode* balanced_node);


AvlTree* AvlTree_build_of_array(
    AvlTreeDataType arr[], int arr_len
);


int AvlTree_insert(
    AvlTree* balanced_tree, AvlTreeDataType* new_data
);


int AvlTree_remove(
    AvlTree* balanced_tree, AvlTreeDataType* data
);


int AvlTree_in_order_println(AvlTree* balanced_tree);


int AvlTree_update_height(AvlTreeNode* adjust_node);


int AvlTree_get_balance_factor(AvlTreeNode* balanced_node);


AvlTreeNode* AvlTree_right_rotate(AvlTreeNode* balanced_node);


AvlTreeNode* AvlTree_left_rotate(AvlTreeNode* balanced_node);


AvlTreeNode* _AvlTree_insert_helper(
    AvlTreeNode* balanced_node, AvlTreeNode* new_node
);


AvlTreeNode* _AvlTree_remove_helper(
    AvlTreeNode* balanced_node, AvlTreeDataType* data
);


void _AvlTree_clean_helper(AvlTreeNode* balanced_node);


void _AvlTree_in_order_traversal(AvlTreeNode* balanced_node);



AvlTreeNode* AvlTreeNode_create(AvlTreeDataType* data);


int AvlTreeNode_clean(AvlTreeNode** balanced_node);


#endif 
