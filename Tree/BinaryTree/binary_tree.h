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
    "BinaryTreeBuildError: Memory initialization failed in process of building BinaryTree\n"

#define BINARY_TREE_COPY_ERROR \
    "BinaryTreeCopyError: Memory initialization failed in BinaryTree copying\n"

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


#define BINARY_TREE_HELP_QUEUE_CREATE_ERROR \
    "BinaryTreeHelpQueueCreateError: Memory initialization of BinaryTreeHelpQueue failed\n"

#define BINARY_TREE_HELP_QUEUE_ACCESS_EXCEPTION \
    "BinaryTreeHelpQueueAccessException: The data address of the BinaryTreeHelpQueue cannot be accessed\n"


#define BINARY_TREE_HELP_QUEUE_NODE_CREATE_ERROR \
    "BinaryTreeHelpQueueNodeCreateError: Memory initialization of BinaryTreeHelpQueueNode failed\n"


typedef int BinaryTreeEleType;


typedef void BinaryTreeContext;


typedef enum BinaryTreeInitModeEnum {
    BINARY_TREE_INIT_DISABLE,
    BINARY_TREE_INIT_ENABLE
} BinaryTreeInitModeEnum;


typedef enum BinaryTreeBuildHelpOrderIndexModeEnum {
    BINARY_TREE_BUILD_ORDER_INDEX_DECREASE,
    BINARY_TREE_BUILD_ORDER_INDEX_INCREASE
} BinaryTreeBuildHelpOrderIndexModeEnum;


typedef struct BinaryTreeNode {
    BinaryTreeEleType data;
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
    BinaryTreeNode** node, BinaryTreeContext* ctx
);


typedef int (*BinaryTreeIterator)(
    BinaryTreeNode** node, BinaryTreeNodeHandler op, BinaryTreeContext* ctx
);


BinaryTree* BinaryTree_create(
    BinaryTreeInitModeEnum init_root, BinaryTreeEleType* root_init_data
);

int BinaryTree_display(BinaryTree* tree, BinaryTreeIterator iter);

BinaryTree* BinaryTree_copy(BinaryTree* tree);

int BinaryTree_clean(BinaryTree** tree);

int BinaryTree_pre_order_traversal(
    BinaryTreeNode** node, BinaryTreeNodeHandler op, BinaryTreeContext* ctx
);

int BinaryTree_in_order_traversal(
    BinaryTreeNode** node, BinaryTreeNodeHandler op, BinaryTreeContext* ctx
);

int BinaryTree_post_order_traversal(
    BinaryTreeNode** node, BinaryTreeNodeHandler op, BinaryTreeContext* ctx
);

int BinaryTree_level_order_traversal(
    BinaryTreeNode** node, BinaryTreeNodeHandler op, BinaryTreeContext* ctx
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

BinaryTreeNode* _BinaryTreeNode_recursion_copy_helper(BinaryTreeNode* node);


BinaryTreeNode* BinaryTreeNode_create(BinaryTreeEleType data);

int BinaryTreeNode_collector(BinaryTreeNode** node, BinaryTreeContext* q);

int BinaryTreeNode_deletor(BinaryTreeNode** node,  BinaryTreeContext* ctx);

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
