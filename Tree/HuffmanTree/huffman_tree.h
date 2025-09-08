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


#define HUFFMAN_TREE_EXTEND_EXCEPTION \
    "HuffmanTreeExtendException: " \
    "The extension of the HuffmanTree failed and src cannot be accessed\n"


#define HUFFMAN_TREE_NODE_CREATE_ERROR \
    "HuffmanTreeNodeCreateError: " \
    "Memory initialization of HuffmanTreeNode failed\n"


#define HUFFMAN_TREE_NODE_ACCESS_EXCEPTION \
    "HuffmanTreeNodeAccessException: " \
    "The data address of the HuffmanTreeNode cannot be accessed\n"


typedef int HuffmanTreeEleType;


typedef int HuffmanTreeWeightType;


typedef void HuffmanTreeHnadleContext;


typedef struct HuffmanTreeNode {
    HuffmanTreeEleType data;
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


int HuffmanTree_extend(HuffmanTree* hf_tree, HuffmanTreeNode* hf_node);


int HuffmanTree_post_order_traverse(
    HuffmanTreeNode* hf_node, HuffmanTreeNodeHandler op, 
    HuffmanTreeHnadleContext* ctx
);


HuffmanTree* HuffmanTree_build_of_weight_array(
    HuffmanTreeEleType ordered_arr[], int len
);


int HuffmanTree_clean_handler(
    HuffmanTreeNode* hf_node, HuffmanTreeHnadleContext* ctx
);


int HuffmanTree_weight_print_handler(
    HuffmanTreeNode* hf_node, HuffmanTreeHnadleContext* ctx
);


HuffmanTreeNode* HuffmanTreeNode_create(
    HuffmanTreeEleType* data, HuffmanTreeWeightType* weight
);


int HuffmanTreeNode_clean(HuffmanTreeNode** hf_node);


#endif
