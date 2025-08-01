#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_


#include <stdio.h>
#include <stdlib.h>


#ifdef __linux__
    #include <sys/types.h>
#endif


// // the exception messages of BinaryTree options
#define BINARY_TREE_CREATE_ERROR \
    "BinaryTreeCreateError: Memory initialization of BinaryTree failed\n"

#define BINARY_TREE_BUILD_ERROR \
    "BinaryTreeBuildError: Memory initialization of BinaryTree failed\n"

#define BINARY_TREE_ACCESS_EXCEPTION \
    "BinaryTreeAccessException: The data address of the BinaryTree cannot be accessed\n"


// the exception messages of BinaryTreeNode options
#define BINARY_TREE_NODE_CREATE_ERROR \
    "BinaryTreeNodeCreateError: Memory initialization of BinaryTreeNode failed\n"

#define BINARY_TREE_NODE_ACCESS_EXCEPTION \
    "BinaryTreeNodeAccessException: The data address of the BinaryTreeNode cannot be accessed\n"


// other misc exception messages of BinaryTree options
#define BINARY_TREE_SRC_ACCESS_EXCEPTION \
    "BinaryTreeSRCAccessException: The data address of the BinaryTree source cannot be accessed\n"


typedef int BinaryTreeEleType;


typedef struct BinaryTreeNode {
    BinaryTreeEleType data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;


typedef struct BinaryTree {
    BinaryTreeNode* root;
    size_t node_num;
    int is_init;
} BinaryTree;


typedef enum BinaryTreeInitModeEnum {
    BINARY_TREE_INIT_DISABLE,
    BINARY_TREE_INIT_ENABLE
} BinaryTreeInitModeEnum;


typedef enum BinaryTreeBuildHelpOrderIndexModeEnum {
    BINARY_TREE_BUILD_ORDER_INDEX_DECREASE,
    BINARY_TREE_BUILD_ORDER_INDEX_INCREASE,
    BINARY_TREE_BUILD_ORDER_INDEX_ALTERNATE
} BinaryTreeBuildHelpOrderIndexModeEnum;


typedef struct _BinaryTreeInnerQueueNode {
    BinaryTreeNode *tree_node;
    struct _BinaryTreeInnerQueueNode *next;
} _BinaryTreeInnerQueueNode;


typedef struct _BinaryTreeInnerQueue {
    _BinaryTreeInnerQueueNode *front;
    _BinaryTreeInnerQueueNode *rear;
} _BinaryTreeInnerQueue;


typedef int (*BinaryTreeNodeOperator)(BinaryTreeNode** node);


typedef int (*BinaryTreeTraversalOperator)
    (BinaryTreeNode* node, BinaryTreeNodeOperator op);


BinaryTree* BinaryTree_create(
    BinaryTreeInitModeEnum init_root, BinaryTreeEleType* root_init_data
);


int BinaryTree_pre_order_traversal(
    BinaryTreeNode* node, BinaryTreeNodeOperator op
);


int BinaryTree_in_order_traversal(
    BinaryTreeNode* node, BinaryTreeNodeOperator op
);


int BinaryTree_post_order_traversal(
    BinaryTreeNode* node, BinaryTreeNodeOperator op
);


int BinaryTree_level_order_traversal(
    BinaryTreeNode* node, BinaryTreeNodeOperator op
);


BinaryTree* 
BinaryTree_build_of_array(BinaryTreeEleType* array, size_t array_len);


BinaryTree* BinaryTree_build_of_pre_order(
    BinaryTreeEleType* in_order, BinaryTreeEleType* pre_order,
    size_t in_len, size_t pre_len
);


BinaryTree* BinaryTree_build_of_post_order(
    BinaryTreeEleType* in_order, BinaryTreeEleType* post_order,
    size_t in_len, size_t post_len
);


BinaryTree* BinaryTree_build_of_level_order(
    BinaryTreeEleType* in_order, BinaryTreeEleType* level_order,
    size_t in_len, size_t level_len
);


ssize_t BinaryTree_in_order_index_search(
    BinaryTreeEleType* in_order, size_t start, size_t end, 
    BinaryTreeEleType val
);


BinaryTreeNode* _BinaryTreeNode_recursion_build_helper(
    BinaryTreeEleType* in_order, BinaryTreeEleType* pre_order, 
    size_t* pre_order_index, size_t in_order_start, size_t in_order_end,
    BinaryTreeBuildHelpOrderIndexModeEnum mode
);


int BinaryTree_display(BinaryTree* tree, BinaryTreeTraversalOperator op);


int BinaryTree_clean(BinaryTree** tree);


BinaryTreeNode* BinaryTreeNode_create(BinaryTreeEleType data);


int BinaryTreeNode_clean(BinaryTreeNode** node);


int BinaryTreeNode_display(BinaryTreeNode** node);


_BinaryTreeInnerQueue* _BinaryTreeInnerQueue_create();


void _BinaryTreeInnerQueue_enqueue(
    _BinaryTreeInnerQueue* q, BinaryTreeNode* tree_node
);


BinaryTreeNode* _BinaryTreeInnerQueue_dequeue(_BinaryTreeInnerQueue* q);


int _BinaryTreeInnerQueue_is_empty(_BinaryTreeInnerQueue* q);


int _BinaryTreeInnerQueue_clean(_BinaryTreeInnerQueue** q);

#endif
