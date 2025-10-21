#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_


#include <stdio.h>
#include <stdlib.h>


#ifdef __linux__
    #include <sys/types.h>
#endif


#define HUFFMAN_TREE_CREATE_ERROR \
    "HuffmanTreeCreateError: " \
    "Memory initialization of HuffmanTree failed\n"


#define HUFFMAN_TREE_BUILD_ERROR \
    "HuffmanTreeBuildError: " \
    "Memory initialization of HuffmanTree failed in building\n"


#define HUFFMAN_TREE_EXTEND_ERROR \
    "HuffmanTreeExtendError: " \
    "Memory initialization of HuffmanTree failed in extension\n"


#define HUFFMAN_TREE_ACCESS_EXCEPTION \
    "HuffmanTreeAccessException: " \
    "The data address of the HuffmanTree cannot be accessed\n"


#define HUFFMAN_TREE_SRC_ACCESS_EXCEPTION \
    "HuffmanTreeExtendException: The  src cannot be accessed\n"


#define HUFFMAN_TREE_NODE_CREATE_ERROR \
    "HuffmanTreeNodeCreateError: " \
    "Memory initialization of HuffmanTreeNode failed\n"


#define HUFFMAN_TREE_NODE_ACCESS_EXCEPTION \
    "HuffmanTreeNodeAccessException: " \
    "The data address of the HuffmanTreeNode cannot be accessed\n"


typedef int HuffmanTreeDataType;


typedef int HuffmanTreeWeightType;


typedef void HuffmanTreeHnadleContext;


typedef struct HuffmanTreeNode {
    HuffmanTreeDataType data;
    HuffmanTreeWeightType weight;
    struct HuffmanTreeNode* left;
    struct HuffmanTreeNode* right;
} HuffmanTreeNode;


typedef struct HuffmanTree {
    HuffmanTreeNode* root;
} HuffmanTree;


typedef int (*HuffmanTreeNodeHandler) (
    HuffmanTreeNode* hf_node, HuffmanTreeHnadleContext* ctx
);


HuffmanTree* HuffmanTree_create();


int HuffmanTree_clean(HuffmanTree** hf_tree);


int HuffmanTree_display(HuffmanTree* hf_tree);


int HuffmanTree_find_two_min_nodes(
    HuffmanTreeNode* arr[], size_t arr_len,
    ssize_t* min1, ssize_t* min2
);


HuffmanTreeNode* HuffmanTree_merge_node(
    HuffmanTreeNode* node1, HuffmanTreeNode* node2
);


HuffmanTree* HuffmanTree_build_of_any_array(
    HuffmanTreeWeightType arr[], size_t arr_len
);


int HuffmanTree_post_order_traverse(
    HuffmanTreeNode* hf_node, HuffmanTreeNodeHandler op, 
    HuffmanTreeHnadleContext* ctx
);


int HuffmanTree_clean_handler(
    HuffmanTreeNode* hf_node, HuffmanTreeHnadleContext* ctx
);


int HuffmanTree_weight_print_handler(
    HuffmanTreeNode* hf_node, HuffmanTreeHnadleContext* ctx
);


HuffmanTreeNode* HuffmanTreeNode_create(
    HuffmanTreeDataType* data, HuffmanTreeWeightType* weight
);


int HuffmanTreeNode_clean(HuffmanTreeNode** hf_node);


#endif
