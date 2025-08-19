#include "thread_binary_tree.h"


#ifdef __linux__
    #include <sys/types.h>
#endif

#include <stdlib.h>


ThreadBinaryTree* ThreadBinaryTree_create() {
    ThreadBinaryTree* tree = 
        (ThreadBinaryTree*) malloc (sizeof(ThreadBinaryTree));

    if (tree == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_CREATE_ERROR);
        return NULL;
    }

    tree->root = NULL;
    tree->node_num = 0;
    return tree;
}


ThreadBinaryTree* 
ThreadBinaryTree_build_of_binary_tree(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, BINARY_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    ThreadBinaryTree* thread_tree = ThreadBinaryTree_create();

    if (thread_tree == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_BUILD_ERROR);
        return NULL;
    }

    ThreadBinaryTreeNode* thread_tree_root = 
        _ThreadBinaryTree_build_of_binary_tree_helper(tree->root);

    if (thread_tree_root == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_BUILD_ERROR);
        ThreadBinaryTree_clean(&thread_tree);
        return NULL;
    }

    thread_tree->node_num = tree->node_num;
    thread_tree->root = thread_tree_root;

    return thread_tree;
}


ThreadBinaryTreeNode* ThreadBinaryTree_threading(BinaryTreeNode* node);


ThreadBinaryTreeNode*
_ThreadBinaryTree_build_of_binary_tree_helper(BinaryTreeNode* node) {
    if (node == NULL) {
        return NULL;
    }

    ThreadBinaryTreeNode* new_th_node = ThreadBinaryTreeNode_create(node->data);

    if (new_th_node == NULL) {
        return NULL;
    }

    new_th_node->left = _ThreadBinaryTree_build_of_binary_tree_helper(node->left);
    new_th_node->right = _ThreadBinaryTree_build_of_binary_tree_helper(node->right);

    return new_th_node;
}


int ThreadBinaryTree_clean(ThreadBinaryTree** t) {
    if (t == NULL || *t == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    return 0;
}


ThreadBinaryTreeNode* 
ThreadBinaryTreeNode_create(ThreadBinaryTreeEleType data) {
    ThreadBinaryTreeNode* node = 
        (ThreadBinaryTreeNode*) malloc (sizeof(ThreadBinaryTreeNode));

    if (node == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_NODE_CREATE_ERROR);
        return NULL;
    }

    node->data = data;
    node->left = node->right = NULL;

    return node;
}


int ThreadBinaryTreeNode_clean(ThreadBinaryTreeNode** node);
