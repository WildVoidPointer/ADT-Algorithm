#include "seq_storage_binary_tree.h"
#include <stdlib.h>
#include <stdio.h>


SeqStorageBinaryTree* SeqStorageBinaryTree_create(size_t size, 
    SeqStorageBinaryTreeInitModeEnum is_init, SeqStorageBinaryTreeEleType* init_data) 
{
    SeqStorageBinaryTree* tree = 
        (SeqStorageBinaryTree*) malloc (sizeof(SeqStorageBinaryTree));
    
    if (tree == NULL) {
        fprintf(stderr, SEQ_STORAGE_BINARY_TREE_CREATE_ERROR);
        return NULL;
    }

    tree->data = 
        (SeqStorageBinaryTreeEleType*) malloc (sizeof(SeqStorageBinaryTreeEleType) * size);

    if (tree->data == NULL) {
        fprintf(stderr, SEQ_STORAGE_BINARY_TREE_CREATE_ERROR);
        free(tree);
        return NULL;
    }

    if (is_init == (SeqStorageBinaryTreeInitModeEnum)SEQ_STORAGE_BINARY_TREE_INIT_ENABLE) {
        tree->is_init = 1;
        tree->init_data = init_data;
        for (size_t i = 0; i < size; i++) {
            tree->data[i] = *init_data;
        }
    } else {
        tree->is_init = 0;
    }

    tree->size = size;
    return tree;
}


SeqStorageBinaryTree* SeqStorageBinaryTree_build_of_array(
    SeqStorageBinaryTreeEleType* array, size_t length)
{
    
}

int SeqStorageBinaryTree_display(SeqStorageBinaryTree* tree);

int SeqStorageBinaryTree_clean(SeqStorageBinaryTree** tree);