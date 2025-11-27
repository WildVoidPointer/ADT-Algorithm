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


int HuffmanTree_destroy(HuffmanTree** hf_tree) {
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


ssize_t HuffmanTree_get_wpl(HuffmanTree* hf_tree) {
    if (hf_tree ==  NULL) {
        fprintf(stderr, HUFFMAN_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    return _HuffmanTree_get_wpl_helper(hf_tree->root, 0);
}


int HuffmanTree_find_two_min_nodes(
    HuffmanTreeNode* arr[], size_t arr_len,
    ssize_t* min1, ssize_t* min2
) {
    if (arr == NULL || min1 == NULL || min2 == NULL
    ) {
        fprintf(stderr, HUFFMAN_TREE_SRC_ACCESS_EXCEPTION);
        return -1;
    }

    *min1 = -1;
    *min2 = -1;

    for (size_t i = 0; i < arr_len; i++) {
        if (arr[i] != NULL) {
            if (*min1 == -1 || arr[i]->weight < arr[(*min1)]->weight) {
                *min2 = *min1;
                *min1 = i;
            } 
            else if (*min2 == -1 || arr[i]->weight < arr[(*min2)]->weight) {
                *min2 = i;
            }
        }
    }

    return 0;
}


HuffmanTreeNode* HuffmanTree_merge_node(
    HuffmanTreeNode* node1, HuffmanTreeNode* node2
) {
    if (node1 == NULL || node2 == NULL) {
        fprintf(stderr, HUFFMAN_TREE_NODE_ACCESS_EXCEPTION);
        return NULL;
    }

    HuffmanTreeWeightType new = (node1->weight + node2->weight);
    HuffmanTreeNode* parent = HuffmanTreeNode_create(NULL, &new);
    if (parent == NULL) {
        return NULL;
    }
    
    parent->left = node1;
    parent->right = node2;
    return parent;
}


HuffmanTree* HuffmanTree_build_of_any_array(
    HuffmanTreeWeightType arr[], size_t arr_len
) {
    if (arr == NULL) {
        fprintf(stderr, HUFFMAN_TREE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    HuffmanTree* hf_tree = HuffmanTree_create();
    if (hf_tree == NULL) {
        fprintf(stderr, HUFFMAN_TREE_BUILD_ERROR);
        return NULL;
    }

    HuffmanTreeNode** hf_nodes = (HuffmanTreeNode**) 
        malloc (arr_len * sizeof(HuffmanTreeNode*));

    for (size_t i = 0; i < arr_len; i++) {
        hf_nodes[i] = HuffmanTreeNode_create(NULL, &arr[i]);
        if (hf_nodes[i] == NULL) {
            fprintf(stderr, HUFFMAN_TREE_BUILD_ERROR);
            for (size_t j = 0; j < i; j++) {
                HuffmanTreeNode_destroy(&hf_nodes[j]);
            }
            HuffmanTree_destroy(&hf_tree);
            free(hf_nodes);
            return NULL;
        }
    }

    size_t remaining = arr_len;

    ssize_t min1;

    ssize_t min2;

    while (remaining > 1) {

        HuffmanTree_find_two_min_nodes(hf_nodes, arr_len, &min1, &min2);

        HuffmanTreeNode* merged = HuffmanTree_merge_node(
            hf_nodes[min1], hf_nodes[min2]
        );

        if (merged == NULL) {
            fprintf(stderr, HUFFMAN_TREE_BUILD_ERROR);
            for (size_t i = 0; i < arr_len; i++) {
                HuffmanTreeNode_destroy(&hf_nodes[i]);
            }
            HuffmanTree_destroy(&hf_tree);
            free(hf_nodes);
            return NULL;
        }

        hf_nodes[min1] = merged;
        hf_nodes[min2] = NULL;

        remaining--;
    }

    HuffmanTreeNode* root = NULL;

    for (size_t i = 0; i < arr_len; i++) {
        if (hf_nodes[i] != NULL) {
            root = hf_nodes[i];
            break;
        }
    }

    hf_tree->root = root;

    free(hf_nodes);

    return hf_tree;
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


size_t _HuffmanTree_get_wpl_helper(
    HuffmanTreeNode* hf_node, size_t depth
) {
    if (hf_node == NULL) {
        return 0;
    }

    if (hf_node->left == NULL && hf_node->right == NULL) {
        return hf_node->weight * depth;
    }

    size_t left_wpl = _HuffmanTree_get_wpl_helper(hf_node->left, depth + 1);
    size_t right_wpl = _HuffmanTree_get_wpl_helper(hf_node->right, depth + 1);

    return left_wpl + right_wpl;
}


HuffmanTreeNode* HuffmanTreeNode_create(
    HuffmanTreeDataType* data, HuffmanTreeWeightType* weight
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


int HuffmanTreeNode_destroy(HuffmanTreeNode** hf_node) {
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
    return HuffmanTreeNode_destroy(&hf_node);
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
