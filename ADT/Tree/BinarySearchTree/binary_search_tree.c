#include "binary_search_tree.h"

#include <stdio.h>
#include <stdlib.h>


BinarySearchTree* BinarySearchTree_create() {
    BinarySearchTree* bs_tree = 
        (BinarySearchTree*) malloc (sizeof(BinarySearchTree));
    if (bs_tree == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_CREATE_ERROR);
        return NULL;
    }

    bs_tree->root = NULL;
    return bs_tree;
}


int BinarySearchTree_destroy(BinarySearchTree** bs_tree) {
    if (bs_tree == NULL || *bs_tree == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    _BinarySearchTree_destroy_helper(&((*bs_tree)->root));

    free(*bs_tree);
    *bs_tree = NULL;
    return 0;
}


BinarySearchTree* BinarySearchTree_build_of_array(
    BinarySearchTreeDataType arr[], int len
) {
    if (arr == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_OTHER_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    BinarySearchTree* bs_tree = BinarySearchTree_create();
    if (bs_tree != NULL) {
        for (int i = 0; i < len; i++) {
            BinarySearchTree_insert(bs_tree, &arr[i]);
        }

        return bs_tree;
    } else {
        fprintf(stderr, BINARY_SEARCH_TREE_BUILD_ERROR);
        return NULL;
    }
}


BinarySearchTreeNode* BinarySearchTree_search(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_key
) {
    if (bs_tree == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    if (bst_key == NULL) {
        fprintf(
            stderr, 
            BINARY_SEARCH_TREE_OTHER_SRC_ACCESS_EXCEPTION
        );
        return NULL;
    }

    BinarySearchTreeNode* curr = bs_tree->root;
    while (curr != NULL && *bst_key != curr->data) {
        if (*bst_key > curr->data) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return curr;
}


int BinarySearchTree_insert(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
) {
    if (bs_tree == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    if (bst_data == NULL) {
        fprintf(
            stderr, 
            BINARY_SEARCH_TREE_OTHER_SRC_ACCESS_EXCEPTION
        );
        return -1;
    }

    return _BinarySearchTree_insert_helper(&(bs_tree->root), bst_data);
}


BinarySearchTreeNode* BinarySearchTree_recur_remove(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
) {
    if (bs_tree == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    if (bst_data == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_OTHER_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    return _BinarySearchTree_remove_helper((&(bs_tree)->root), bst_data);
}


BinarySearchTreeNode* BinarySearchTree_iter_remove(
    BinarySearchTree* bs_tree, BinarySearchTreeDataType* bst_data
) {
    if (bs_tree == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    BinarySearchTreeNode* curr = bs_tree->root;

    BinarySearchTreeNode* to_delete = NULL;

    BinarySearchTreeNode* prev = NULL;

    while (curr != NULL && (*bst_data) != curr->data) {
        prev = curr;
        if ((*bst_data) > curr->data) {
            curr = curr->right;
        } else if ((*bst_data < curr->data)){
            curr = curr->left;
        }
    }

    if (curr == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_REMOVE_EXCEPTION);
        return NULL;
    } else {
        to_delete = curr;
    }

    if (curr->left != NULL && curr->right != NULL) {
        BinarySearchTreeNode* inorder_first = curr;
        BinarySearchTreeNode* inorder_first_prev = NULL;
        
        while (inorder_first->left != NULL) {
            inorder_first_prev = inorder_first;
            inorder_first = inorder_first->left;
        }

        _BinarySearchTreeNode_set_by_node(curr, inorder_first);

        curr = inorder_first;
        prev = inorder_first_prev;
    }

    BinarySearchTreeNode* child = NULL;

    if (curr->left != NULL) {
        child = curr->left;
    } else {
        child = curr->right;
    }

    // 若被删除节点为根节点
    if (prev ==  NULL) {
        bs_tree->root = child;
    } else {
        if (prev->left == curr) {
            prev->left = child;
        } else {
            prev->right = child;
        }
    }

    return to_delete;
}


int _BinarySearchTree_insert_helper(
    BinarySearchTreeNode** bst_node, BinarySearchTreeDataType* bst_data
) {
    if (*bst_node == NULL) {
        BinarySearchTreeNode* new_bst_node = BinarySearchTreeNode_create(bst_data);
        if (new_bst_node == NULL) {
            fprintf(stderr, BINARY_SEARCH_TREE_INSERT_ERROR);
            return -1;
        }

        *bst_node = new_bst_node;
        return 0;
    } else if (*bst_data == (*bst_node)->data) {
        fprintf(stderr, BINARY_SEARCH_TREE_INSERT_EXCEPTION);
        return -1;
    } else if (*bst_data < (*bst_node)->data) {
        return _BinarySearchTree_insert_helper(&((*bst_node)->left), bst_data);
    } else {
        return _BinarySearchTree_insert_helper(&((*bst_node)->right), bst_data);
    }
}


BinarySearchTreeNode* _BinarySearchTree_remove_helper(
    BinarySearchTreeNode** bst_node, BinarySearchTreeDataType* bst_data
) {
    if (bst_node == NULL || *bst_node == NULL || bst_data == NULL) {
        return NULL;
    }

    if (*bst_data < (*bst_node)->data) {

        (*bst_node)->left = _BinarySearchTree_remove_helper(
            &((*bst_node)->left), bst_data
        );

    } else if (*bst_data > (*bst_node)->data) {

        (*bst_node)->right = _BinarySearchTree_remove_helper(
            &((*bst_node)->right), bst_data
        );

    } else {

        if ((*bst_node)->left == NULL) {

            BinarySearchTreeNode* bst_node_tmp = (*bst_node)->right;
            BinarySearchTreeNode_destroy(bst_node);
            return bst_node_tmp;
            
        } else if ((*bst_node)->right == NULL) {

            BinarySearchTreeNode* bst_node_tmp = (*bst_node)->left;
            BinarySearchTreeNode_destroy(bst_node);
            return bst_node_tmp;
        }

        BinarySearchTreeNode* in_order_first_node = (*bst_node)->right;

        while (in_order_first_node->left != NULL) {
            in_order_first_node = in_order_first_node->left;
        }

        (*bst_node)->data = in_order_first_node->data;

        (*bst_node)->right = _BinarySearchTree_remove_helper(
            (&(*bst_node)->right), 
            &(in_order_first_node->data)
        );
    }

    return (*bst_node);
}


int _BinarySearchTree_destroy_helper(BinarySearchTreeNode** bst_node) {
    if (bst_node != NULL && *bst_node != NULL) {
        _BinarySearchTree_destroy_helper(&((*bst_node)->left));
        _BinarySearchTree_destroy_helper(&((*bst_node)->right));
        BinarySearchTreeNode_destroy(bst_node);
        return 0;
    } else {
        return -1;
    }
}



BinarySearchTreeNode* 
BinarySearchTreeNode_create(BinarySearchTreeDataType* bst_data) {
    if (bst_data == NULL) {
        fprintf(
            stderr,
            BINARY_SEARCH_TREE_NODE_SRC_ACCESS_EXCEPTION
        );
        return NULL;
    }

    BinarySearchTreeNode* bst_node = 
        (BinarySearchTreeNode*) malloc (sizeof(BinarySearchTreeNode));
    if (bst_node == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_NODE_CREATE_ERROR);
        return NULL;
    }

    bst_node->data = *bst_data;
    bst_node->left = bst_node->right = NULL;
    return bst_node;
}


int BinarySearchTreeNode_destroy(BinarySearchTreeNode** bst_node) {
    if (bst_node == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    free(*bst_node);
    *bst_node = NULL;
    return 0;
}


int _BinarySearchTreeNode_set_by_node(
    BinarySearchTreeNode* dest, BinarySearchTreeNode* src
) {
    if (dest == NULL || src == NULL) {
        fprintf(stderr, BINARY_SEARCH_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    dest->data = src->data;
    return 0;
}
