#include "huffman_tree.h"


HuffmanTree* HuffmanTree_create() {
    HuffmanTree* hf_tree = (HuffmanTree*) malloc (sizeof(HuffmanTree));
    if (hf_tree == NULL) {
        fprintf(stderr, HUFFMAN_TREE_CREATE_ERROR);
        return NULL;
    }

    hf_tree->root = NULL;
    return hf_tree;
}


int HuffmanTree_clean(HuffmanTree** hf_tree) {
    if (hf_tree == NULL || *hf_tree == NULL) {
        fprintf(stderr, HUFFMAN_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    HuffmanTree_post_order_traverse(
        (*hf_tree)->root, HuffmanTree_clean_handler, NULL
    );

    free(*hf_tree);
    *hf_tree =NULL;
    return 0;
}


int HuffmanTree_display(HuffmanTree* hf_tree) {
    if (hf_tree == NULL) {
        fprintf(stderr, HUFFMAN_TREE_ACCESS_EXCEPTION);
        return -1;
    }
    printf("HuffmanTree: {  ");
    HuffmanTree_post_order_traverse(
        hf_tree->root, HuffmanTree_weight_print_handler, NULL
    );
    printf("}\n");
    return 0;
}


int HuffmanTree_extend(HuffmanTree* hf_tree, HuffmanTreeNode* hf_node) {
    if (hf_tree == NULL || hf_node == NULL) {
        fprintf(stderr, HUFFMAN_TREE_EXTEND_EXCEPTION);
        return -1;
    }

    if (hf_tree->root == NULL) {
        HuffmanTreeNode* hf_root = HuffmanTreeNode_create(NULL, NULL);
        if (hf_root == NULL) {
            fprintf(stderr, HUFFMAN_TREE_EXTEND_ERROR);
            return -1;
        }
        hf_tree->root = hf_root;
    }

    if (hf_tree->root->right == NULL) {
        hf_tree->root->right = hf_node;
        
    } else if (
        hf_tree->root->right != NULL && hf_tree->root->left == NULL
    ) {
        hf_tree->root->left = hf_node;

    } else {
        HuffmanTreeNode* hf_ext_node = HuffmanTreeNode_create(
            NULL, &(hf_tree->root->weight)
        );
        if (hf_ext_node == NULL) {
            fprintf(stderr, HUFFMAN_TREE_EXTEND_ERROR);
            return -1;
        }
        hf_ext_node->right = hf_tree->root;
        hf_ext_node->left = hf_node;
        hf_tree->root = hf_ext_node;
    }

    hf_tree->root->weight += hf_node->weight;

    return 0;
}


int HuffmanTree_post_order_traverse(
    HuffmanTreeNode* hf_node, HuffmanTreeNodeHandler op, 
    HuffmanTreeHnadleContext* ctx
) {
    if (hf_node != NULL || op == NULL) {
        HuffmanTree_post_order_traverse(hf_node->left, op, ctx);
        HuffmanTree_post_order_traverse(hf_node->right, op, ctx);
        op(hf_node, ctx);
        return 0;

    } else {
        return -1;
    }
}


HuffmanTree* HuffmanTree_build_of_weight_array(
    HuffmanTreeEleType ordered_arr[], int len
) {
    HuffmanTree* hf_tree = HuffmanTree_create();
    if (hf_tree == NULL) {
        fprintf(stderr, HUFFMAN_TREE_BUILD_ERROR);
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        HuffmanTreeNode* new_hf_node = HuffmanTreeNode_create(NULL, &ordered_arr[i]);
        if (new_hf_node == NULL) {
            fprintf(stderr, HUFFMAN_TREE_BUILD_ERROR);
            HuffmanTree_clean(&hf_tree);
            return NULL;
        }

        int extend_re_code = HuffmanTree_extend(hf_tree, new_hf_node);
        if (extend_re_code == -1) {
            fprintf(stderr, HUFFMAN_TREE_BUILD_ERROR);
            HuffmanTree_clean(&hf_tree);
            return NULL;
        }
    }
    return hf_tree;
}


HuffmanTreeNode* HuffmanTreeNode_create(
    HuffmanTreeEleType* data, HuffmanTreeWeightType* weight
) {
    HuffmanTreeNode* hf_node = 
        (HuffmanTreeNode*) malloc (sizeof(HuffmanTreeNode));
    if (hf_node == NULL) {
        fprintf(stderr, HUFFMAN_TREE_NODE_CREATE_ERROR);
        return NULL;
    }

    if (data != NULL) {
        hf_node->data = *data;
    }

    if (weight != NULL) {
        hf_node->weight = *weight;
    }

    hf_node->left = hf_node->right = NULL;

    return hf_node;
}


int HuffmanTreeNode_clean(HuffmanTreeNode** hf_node) {
    if (hf_node == NULL || *hf_node == NULL) {
        fprintf(stderr, HUFFMAN_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    free(*hf_node);
    *hf_node = NULL;
    return 0;
}


int HuffmanTree_clean_handler(
    HuffmanTreeNode* hf_node, HuffmanTreeHnadleContext* ctx
) {
    return HuffmanTreeNode_clean(&hf_node);
}


int HuffmanTree_weight_print_handler(
    HuffmanTreeNode* hf_node, HuffmanTreeHnadleContext* ctx
) {
    if (hf_node == NULL) {
        fprintf(stderr, HUFFMAN_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    printf("%d  ", hf_node->weight);
    return 0;
}
