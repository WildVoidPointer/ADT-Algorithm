#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_


#include <stdio.h>
#include <stdlib.h>


#ifdef __linux__
    #include <sys/types.h>
#endif


// // the exception messages of BinaryTree options
#define BINARY_TREE_CREATE_ERROR \
    "BinaryTreeCreateError: " \
    "Memory initialization of BinaryTree failed\n"


#define BINARY_TREE_BUILD_ERROR \
    "BinaryTreeBuildError: " \
    "Memory initialization failed in process of building BinaryTree\n"


#define BINARY_TREE_COPY_ERROR \
    "BinaryTreeCopyError: " \
    "Memory initialization failed in BinaryTree copying\n"


#define BINARY_TREE_ACCESS_EXCEPTION \
    "BinaryTreeAccessException: " \
    "The data address of the BinaryTree cannot be accessed\n"


// the exception messages of BinaryTreeNode options
#define BINARY_TREE_NODE_CREATE_ERROR \
    "BinaryTreeNodeCreateError: " \
    "Memory initialization of BinaryTreeNode failed\n"


#define BINARY_TREE_NODE_ACCESS_EXCEPTION \
    "BinaryTreeNodeAccessException: " \
    "The data address of the BinaryTreeNode cannot be accessed\n"


// other misc exception messages of BinaryTree options
#define BINARY_TREE_SRC_ACCESS_EXCEPTION \
    "BinaryTreeSRCAccessException: " \
    "The data address of the BinaryTree source cannot be accessed\n"


#define BINARY_TREE_HELP_QUEUE_CREATE_ERROR \
    "BinaryTreeHelpQueueCreateError: " \
    "Memory initialization of BinaryTreeHelpQueue failed\n"


#define BINARY_TREE_HELP_QUEUE_ACCESS_EXCEPTION \
    "BinaryTreeHelpQueueAccessException: " \
    "The data address of the BinaryTreeHelpQueue cannot be accessed\n"


#define BINARY_TREE_HELP_QUEUE_NODE_CREATE_ERROR \
    "BinaryTreeHelpQueueNodeCreateError: " \
    "Memory initialization of BinaryTreeHelpQueueNode failed\n"


typedef int BinaryTreeDataType;


typedef void BinaryTreeHandleContext;


typedef enum BinaryTreeInitModeEnum {
    BINARY_TREE_INIT_DISABLE,
    BINARY_TREE_INIT_ENABLE
} BinaryTreeInitModeEnum;


typedef enum BinaryTreeBuildHelpOrderIndexModeEnum {
    BINARY_TREE_BUILD_ORDER_INDEX_DECREASE,
    BINARY_TREE_BUILD_ORDER_INDEX_INCREASE
} BinaryTreeBuildHelpOrderIndexModeEnum;


typedef struct BinaryTreeNode {
    BinaryTreeDataType data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;


typedef struct BinaryTree {
    BinaryTreeNode* root;
    size_t node_num;
} BinaryTree;


typedef struct BinaryTreeHelpQueueNode {
    BinaryTreeNode *tree_node;
    struct BinaryTreeHelpQueueNode *next;
} BinaryTreeHelpQueueNode;


typedef struct BinaryTreeHelpQueue {
    BinaryTreeHelpQueueNode *front;
    BinaryTreeHelpQueueNode *rear;
} BinaryTreeHelpQueue;


typedef int (*BinaryTreeNodeHandler)(
    BinaryTreeNode* node, BinaryTreeHandleContext* ctx
);


typedef int (*BinaryTreeTraverser)(
    BinaryTreeNode* node, BinaryTreeNodeHandler op, BinaryTreeHandleContext* ctx
);


BinaryTree* BinaryTree_create(
    BinaryTreeInitModeEnum init_root, BinaryTreeDataType* root_init_data
);


int BinaryTree_display(BinaryTree* tree, BinaryTreeTraverser traverser);


BinaryTree* BinaryTree_copy(BinaryTree* tree);


int BinaryTree_clean(BinaryTree** tree);


int BinaryTree_pre_order_traverse(
    BinaryTreeNode* node, BinaryTreeNodeHandler op, BinaryTreeHandleContext* ctx
);


int BinaryTree_in_order_traverse(
    BinaryTreeNode* node, BinaryTreeNodeHandler op, BinaryTreeHandleContext* ctx
);


int BinaryTree_post_order_traverse(
    BinaryTreeNode* node, BinaryTreeNodeHandler op, BinaryTreeHandleContext* ctx
);


int BinaryTree_level_order_traverse(
    BinaryTreeNode* node, BinaryTreeNodeHandler op, BinaryTreeHandleContext* ctx
);


BinaryTree* BinaryTree_build_of_array(
    BinaryTreeDataType* array, size_t array_len
);


BinaryTree* BinaryTree_build_of_pre_order(
    BinaryTreeDataType* in_order, BinaryTreeDataType* pre_order,
    size_t in_len, size_t pre_len
);


BinaryTree* BinaryTree_build_of_post_order(
    BinaryTreeDataType* in_order, BinaryTreeDataType* post_order,
    size_t in_len, size_t post_len
);


BinaryTree* BinaryTree_build_of_level_order(
    BinaryTreeDataType* in_order, BinaryTreeDataType* level_order,
    size_t in_len, size_t level_len
);


ssize_t BinaryTree_in_order_index_search(
    BinaryTreeDataType* in_order, size_t start, size_t end, 
    BinaryTreeDataType val
);


int BinaryTree_collect_handler(BinaryTreeNode* node, BinaryTreeHandleContext* q);


int BinaryTree_clean_handler(BinaryTreeNode* node,  BinaryTreeHandleContext* ctx);


BinaryTreeNode* _BinaryTreeNode_recursion_build_helper(
    BinaryTreeDataType* in_order, BinaryTreeDataType* pre_order, 
    size_t* pre_order_index, size_t in_order_start, size_t in_order_end,
    BinaryTreeBuildHelpOrderIndexModeEnum mode
);


BinaryTreeNode* _BinaryTreeNode_recursion_copy_helper(BinaryTreeNode* node);



BinaryTreeNode* BinaryTreeNode_create(BinaryTreeDataType data);


int BinaryTreeNode_clean(BinaryTreeNode** node);


int BinaryTreeNode_display(BinaryTreeNode* node);



BinaryTreeHelpQueue* BinaryTreeHelpQueue_create();


int BinaryTreeHelpQueue_enqueue(
    BinaryTreeHelpQueue* q, BinaryTreeNode* tree_node
);


BinaryTreeNode* BinaryTreeHelpQueue_dequeue(BinaryTreeHelpQueue* q);


int BinaryTreeHelpQueue_is_empty(BinaryTreeHelpQueue* q);


int BinaryTreeHelpQueue_clean_without_free_node(BinaryTreeHelpQueue** q);

#endif
