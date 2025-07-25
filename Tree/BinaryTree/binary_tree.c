#include "binary_tree.h"
#include <stdlib.h>
#include <stdio.h>


BinaryTree* BinaryTree_create(
    BinaryTreeInitModeEnum init_root, BinaryTreeEleType* root_init_data)
{
    BinaryTree* tree = (BinaryTree*) malloc (sizeof(BinaryTree));
    if (tree == NULL) {
        fprintf(stderr, BINARY_TREE_CREATE_ERROR);
        return NULL;
    }

    if (init_root == BINARY_TREE_INIT_ENABLE) {
        BinaryTreeNode* tmp = BinaryTreeNode_create(*root_init_data);

        if (tmp == NULL) {
            free(tree);
            fprintf(stderr, BINARY_TREE_CREATE_ERROR);
            return NULL;
        } else {
            tree->root = tmp;
        }

        tree->node_num = 1;

    } else {
        tree->node_num = 0;
        tree->root =  NULL;
    }

    return tree;
}


BinaryTree* 
BinaryTree_build_of_array(BinaryTreeEleType* array, size_t array_len) {
    if (array == NULL) {
        fprintf(stderr, BINARY_TREE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    BinaryTree* tree = BinaryTree_create(BINARY_TREE_INIT_DISABLE, NULL);

    if(tree == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        return NULL;
    }

    BinaryTreeNode* root = BinaryTreeNode_create(array[0]);
    _BinaryTreeInnerQueue* q = _BinaryTreeInnerQueue_create();
    _BinaryTreeInnerQueue_enqueue(q, root);
    
    int i = 1;
    while (i < array_len && !_BinaryTreeInnerQueue_is_empty(q)) {
        BinaryTreeNode* current = _BinaryTreeInnerQueue_dequeue(q);
        
        // 处理左子节点
        if (i < array_len) {
            current->left = BinaryTreeNode_create(array[i]);
            _BinaryTreeInnerQueue_enqueue(q, current->left);
        }
        i++;
        
        // 处理右子节点
        if (i < array_len) {
            current->right = BinaryTreeNode_create(array[i]);
            _BinaryTreeInnerQueue_enqueue(q, current->right);
        }
        i++;
    }
    
    free(q);
    tree->root = root;
    tree->node_num = array_len;
    return tree;
}


int BinaryTree_pre_order_traversal(
    BinaryTreeNode* node, BinaryTreeNodeOperator op) 
{
    if (node != NULL) {
        if (op != NULL) {
            op(&node);
        } else {
            return -1;
        }

        BinaryTree_pre_order_traversal(node->left, op);
        BinaryTree_pre_order_traversal(node->right, op);
    } else {
        return -1;
    }

    return 0;
}


int BinaryTree_in_order_traversal(
    BinaryTreeNode* node, BinaryTreeNodeOperator op)
{
    if (node != NULL) {
        BinaryTree_in_order_traversal(node->left, op);

        if (op != NULL) {
            op(&node);
        } else {
            return -1;
        }

        BinaryTree_in_order_traversal(node->right, op);
    } else {
        return -1;
    }

    return 0;
}


int BinaryTree_post_order_traversal(
    BinaryTreeNode* node, BinaryTreeNodeOperator op)
{
    if (node != NULL) {
        BinaryTree_post_order_traversal(node->left, op);
        BinaryTree_post_order_traversal(node->right, op);

        if (op != NULL) {
            op(&node);
        } else {
            return -1;
        }

    } else {
        return -1;
    }

    return 0;
}


int BinaryTree_level_order_traversal(
    BinaryTreeNode* node, BinaryTreeNodeOperator op)
{
    if (node != NULL) {
        BinaryTreeNode* tmp_node;
        _BinaryTreeInnerQueue* q = _BinaryTreeInnerQueue_create();
        _BinaryTreeInnerQueue_enqueue(q, node);

        if (op != NULL) {
            while (!_BinaryTreeInnerQueue_is_empty(q)) {

                tmp_node = _BinaryTreeInnerQueue_dequeue(q);

                if (tmp_node->left !=  NULL) {
                    _BinaryTreeInnerQueue_enqueue(q, tmp_node->left);
                }

                if (tmp_node->right !=  NULL) {
                    _BinaryTreeInnerQueue_enqueue(q, tmp_node->right);
                }

                op(&tmp_node);
            }

            free(q);
        } 
        return 0;
    } else {
        return -1;
    }
}


int BinaryTree_display(BinaryTree* tree, BinaryTreeTraversalOperator op) {
    if (tree == NULL) {
        fprintf(stderr, BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    printf("BinaryTree: {  ");
    if (op == NULL) {
        BinaryTree_level_order_traversal(tree->root, BinaryTreeNode_display);
    } else {
        op(tree->root, BinaryTreeNode_display);
    }
    printf("}\n");
}


BinaryTree* BinaryTree_build_of_pre_order(
    BinaryTreeEleType* in_order, BinaryTreeEleType* pre_order,
    size_t in_len, size_t pre_len
) {
    if (in_order == NULL || pre_order == NULL) {
        fprintf(stderr, BINARY_TREE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    BinaryTree* tree = BinaryTree_create(BINARY_TREE_INIT_DISABLE, NULL);
    if (tree == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        return NULL;
    }

    size_t pre_order_index = 0;

    BinaryTreeNode* node = BinaryTreeNode_build_of_pre_order(
        in_order, pre_order, &pre_order_index, 0, in_len - 1
    );

    if (node == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        free(tree);
        return NULL;
    } else {
        tree->root = node;
        tree->node_num = in_len;
        return NULL;
    }
}


ssize_t BinaryTree_in_order_index_search(
    BinaryTreeEleType* in_order, size_t start, size_t end, 
    BinaryTreeEleType val)
{
    for (size_t i = start; i <= end; i++) {
        if (in_order[i] == val)
            return i;
    }
    return -1;
}


int BinaryTree_clean(BinaryTree** tree) {
    if (tree == NULL || *tree == NULL) {
        fprintf(stderr, BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    BinaryTree_post_order_traversal((*tree)->root, BinaryTreeNode_clean);

    free(*tree);
    *tree = NULL;
    return 0;
}


BinaryTreeNode* BinaryTreeNode_create(BinaryTreeEleType data) {
    BinaryTreeNode* node = 
        (BinaryTreeNode*) malloc (sizeof(BinaryTreeNode));

    if (node == NULL) {
        fprintf(stderr, BINARY_TREE_NODE_CREATE_ERROR);
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}


int BinaryTreeNode_clean(BinaryTreeNode** node) {
    if (node == NULL || *node == NULL) {
        fprintf(stderr, BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    free(*node);
    *node = NULL;
    return 0;
}


int BinaryTreeNode_display(BinaryTreeNode** node) {
    if (node == NULL || *node == NULL) {
        fprintf(stderr, BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    printf("%d  ", (*node)->data);
    return 0;
}


_BinaryTreeInnerQueue* _BinaryTreeInnerQueue_create() {
    _BinaryTreeInnerQueue* q = 
        (_BinaryTreeInnerQueue*)malloc(sizeof(_BinaryTreeInnerQueue));

    q->front = q->rear = NULL;
    return q;
}


void _BinaryTreeInnerQueue_enqueue(
    _BinaryTreeInnerQueue* q, BinaryTreeNode* tree_node) 
{

    _BinaryTreeInnerQueueNode* new_node = 
        (_BinaryTreeInnerQueueNode*) 
        malloc (sizeof(_BinaryTreeInnerQueueNode));

    new_node->tree_node = tree_node;
    new_node->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}


BinaryTreeNode* _BinaryTreeInnerQueue_dequeue(_BinaryTreeInnerQueue* q) {
    if (q->front == NULL) return NULL;
    
    _BinaryTreeInnerQueueNode* temp = q->front;
    BinaryTreeNode* tree_node = temp->tree_node;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return tree_node;
}


int _BinaryTreeInnerQueue_is_empty(_BinaryTreeInnerQueue* q) {
    return q->front == NULL;
}
