#ifndef THREAD_BINARY_TREE_H
#define THREAD_BINARY_TREE_H


#ifdef __linux__
    #include <sys/types.h>
#endif

#include <stdlib.h>


#include "../BinaryTree/binary_tree.h"


#define THREAD_BINARY_TREE_CREATE_ERROR \
    "ThreadBinaryTreeCreateError: " \
    "Memory initialization of ThreadBinaryTree failed\n"

#define THREAD_BINARY_TREE_BUILD_ERROR \
    "ThreadBinaryTreeBuildError: " \
    "Memory initialization failed in ThreadBinaryTree building\n"

#define THREAD_BINARY_TREE_ACCESS_EXCEPTION \
    "ThreadBinaryTreeAccessException: " \
    "The data address of the ThreadBinaryTree cannot be accessed\n"


#define THREAD_BINARY_TREE_NODE_CREATE_ERROR \
    "ThreadBinaryTreeNodeCreateError: " \
    "Memory initialization of ThreadBinaryTreeNode failed\n"


typedef int ThreadBinaryTreeEleType;


typedef void ThreadBinaryTreeHandleContext;


typedef enum ThreadBinaryTreeIndexStateEnum {
    THREAD_BINARY_TREE_LEFT_IS_NOT_PRECURSOR = 0,
    THREAD_BINARY_TREE_LEFT_IS_PRECURSOR = 1,
    THREAD_BINARY_TREE_RIGHT_IS_NOT_SUCCESSOR = 0,
    THREAD_BINARY_TREE_RIGHT_IS_SUCCESSOR = 1,
} ThreadBinaryTreeIndexStateEnum;


typedef struct ThreadBinaryTreeNode {
    ThreadBinaryTreeEleType data;
    struct ThreadBinaryTreeNode* left;
    struct ThreadBinaryTreeNode* right;
    ThreadBinaryTreeIndexStateEnum left_is_precursor;
    ThreadBinaryTreeIndexStateEnum right_is_successor;
} ThreadBinaryTreeNode;


typedef struct ThreadBinaryTree {
    ThreadBinaryTreeNode* root;
    size_t node_num;
    int is_threaded;
} ThreadBinaryTree;


typedef struct ThreadBinaryTreeThreadingContext {
    ThreadBinaryTreeNode* prev;
} ThreadBinaryTreeThreadingContext;


typedef int (*ThreadBinaryTreeHandler) (
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandleContext* th_ctx
);


ThreadBinaryTree* ThreadBinaryTree_create();


ThreadBinaryTree* 
ThreadBinaryTree_build_of_binary_tree(BinaryTree* bin_tree);


int ThreadBinaryTree_in_order_traversal(
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandler th_handler, 
    ThreadBinaryTreeHandleContext* th_ctx
);


int ThreadBinaryTree_linked_traversal(
    ThreadBinaryTreeNode* th_root, ThreadBinaryTreeHandler th_handler, 
    ThreadBinaryTreeHandleContext* th_ctx
);


int ThreadBinaryTree_threading_handler(
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandleContext* th_prev
);


int ThreadBinaryTree_threading(ThreadBinaryTree* th_tree);


ThreadBinaryTreeNode*
_ThreadBinaryTree_build_of_binary_tree_helper(BinaryTreeNode* bin_node);


int ThreadBinaryTree_clean(ThreadBinaryTree** th_tree);



ThreadBinaryTreeNode* 
ThreadBinaryTreeNode_create(ThreadBinaryTreeEleType data);


int ThreadBinaryTreeNode_clean(ThreadBinaryTreeNode** node);


#endif
