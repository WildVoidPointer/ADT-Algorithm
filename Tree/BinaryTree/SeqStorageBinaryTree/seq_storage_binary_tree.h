#ifndef SEQ_STORAGE_BINARY_TREE_H
#define SEQ_STORAGE_BINARY_TREE_H


#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define SEQ_STORAGE_BINARY_TREE_CREATE_ERROR \
    "SeqStorageBinaryTreeCreateError: Memory initialization of SeqStorageBinaryTree failed\n"


typedef int SeqStorageBinaryTreeEleType;


typedef struct SeqStorageBinaryTree {
    SeqStorageBinaryTreeEleType* data;
    SeqStorageBinaryTreeEleType init_data;
    size_t size;
    int is_init;
} SeqStorageBinaryTree;


typedef enum SeqStorageBinaryTreeInitModeEnum {
    SEQ_STORAGE_BINARY_TREE_INIT_DISABLE,
    SEQ_STORAGE_BINARY_TREE_INIT_ENABLE
} SeqStorageBinaryTreeInitModeEnum;


SeqStorageBinaryTree* 
SeqStorageBinaryTree_create(
    size_t size, 
    SeqStorageBinaryTreeInitModeEnum is_init, 
    SeqStorageBinaryTreeEleType* init_data
);

SeqStorageBinaryTree*
SeqStorageBinaryTree_build_of_array(
    SeqStorageBinaryTreeEleType* array, 
    size_t length
);

int SeqStorageBinaryTree_display(SeqStorageBinaryTree* tree);

int SeqStorageBinaryTree_clean(SeqStorageBinaryTree** tree);


#endif
