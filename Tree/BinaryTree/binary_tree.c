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


int BinaryTree_display(BinaryTree* tree, BinaryTreeTraverser traverser) {

    if (tree == NULL) {
        fprintf(stderr, BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    BinaryTreeHelpQueue* q = BinaryTreeHelpQueue_create();

    if (traverser == NULL) {
        BinaryTree_level_order_traverse(tree->root, BinaryTree_collect_handler, q);
    } else {
        traverser(tree->root, BinaryTree_collect_handler, q);
    }


    printf("BinaryTree: {  ");
    while (!BinaryTreeHelpQueue_is_empty(q)) {
        BinaryTreeNode_display(BinaryTreeHelpQueue_dequeue(q));
    }
    printf("}\n");

    BinaryTreeHelpQueue_clean_without_free_node(&q);

    return 0;
}


BinaryTree* BinaryTree_copy(BinaryTree* tree) {
    if (tree == NULL) {
        fprintf(stderr, BINARY_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    BinaryTree* new_tree = BinaryTree_create(BINARY_TREE_INIT_DISABLE, NULL);

    if (new_tree == NULL) {
        fprintf(stderr, BINARY_TREE_COPY_ERROR);
        return NULL;
    }

    BinaryTreeNode* new_tree_root = 
        _BinaryTreeNode_recursion_copy_helper(tree->root);

    if (new_tree_root == NULL) {
        fprintf(stderr, BINARY_TREE_COPY_ERROR);
        BinaryTree_clean(&new_tree);
        return NULL;
    }

    new_tree->root = new_tree_root;
    new_tree->node_num = tree->node_num;
    return new_tree;
}


int BinaryTree_clean(BinaryTree** tree) {
    if (tree == NULL || *tree == NULL) {
        fprintf(stderr, BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    BinaryTree_post_order_traverse((*tree)->root, BinaryTree_clean_handler, NULL);
    
    free(*tree);
    *tree = NULL;
    return 0;
}


int BinaryTree_pre_order_traverse(
    BinaryTreeNode* node, BinaryTreeNodeHandler op, BinaryTreeContext* ctx
) {
    if (node != NULL && op != NULL) {
        BinaryTreeNode* left = node->left;
        BinaryTreeNode* right = node->right;

        op(node, ctx);
        BinaryTree_pre_order_traverse(left, op, ctx);
        BinaryTree_pre_order_traverse(right, op, ctx);
    } else {
        return -1;
    }

    return 0;
}


int BinaryTree_in_order_traverse(
    BinaryTreeNode* node, BinaryTreeNodeHandler op, BinaryTreeContext* ctx
) {
    if (node != NULL && op != NULL) {
        BinaryTreeNode* right = node->right;
        BinaryTree_in_order_traverse(node->left, op, ctx);
        op(node, ctx);
        BinaryTree_in_order_traverse(right, op, ctx);
    } else {
        return -1;
    }

    return 0;
}


int BinaryTree_post_order_traverse(
    BinaryTreeNode* node, BinaryTreeNodeHandler op, BinaryTreeContext* ctx
) {
    if (node != NULL && op != NULL) {
        BinaryTree_post_order_traverse(node->left, op, ctx);
        BinaryTree_post_order_traverse(node->right, op, ctx);
        op(node, ctx);
    } else {
        return -1;
    }

    return 0;
}


int BinaryTree_level_order_traverse(
    BinaryTreeNode* node, BinaryTreeNodeHandler op, BinaryTreeContext* ctx
) {
    if (node != NULL && op != NULL) {

        BinaryTreeNode* tmp_node;
        BinaryTreeHelpQueue* q = BinaryTreeHelpQueue_create();
        BinaryTreeHelpQueue_enqueue(q, node);
       
        while (!BinaryTreeHelpQueue_is_empty(q)) {

            tmp_node = BinaryTreeHelpQueue_dequeue(q);

            if (tmp_node->left !=  NULL) {
                BinaryTreeHelpQueue_enqueue(q, tmp_node->left);
            }

            if (tmp_node->right !=  NULL) {
                BinaryTreeHelpQueue_enqueue(q, tmp_node->right);
            }

            op(tmp_node, ctx);
        }

        BinaryTreeHelpQueue_clean_without_free_node(&q);
        return 0;

    } else {
        return -1;
    }
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
    if (root == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        BinaryTree_clean(&tree);
        return NULL;
    }

    BinaryTreeHelpQueue* help_queue = BinaryTreeHelpQueue_create();
    if (help_queue == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        BinaryTree_clean(&tree);
        BinaryTreeNode_clean(&root);
        return NULL;
    }

    BinaryTreeHelpQueue_enqueue(help_queue, root);

    int build_abort = 0;
    
    int i = 1;
    while (i < array_len && !BinaryTreeHelpQueue_is_empty(help_queue)) {
        BinaryTreeNode* current = BinaryTreeHelpQueue_dequeue(help_queue);
        
        // 处理左子节点
        if (i < array_len) {
            current->left = BinaryTreeNode_create(array[i]);
            if (current->left == NULL) {
                fprintf(stderr, BINARY_TREE_BUILD_ERROR);
                build_abort = 1;
                break;
            }

            BinaryTreeHelpQueue_enqueue(help_queue, current->left);
        }
        i++;
        
        // 处理右子节点
        if (i < array_len) {
            current->right = BinaryTreeNode_create(array[i]);
            if (current->right == NULL) {
                fprintf(stderr, BINARY_TREE_BUILD_ERROR);
                build_abort = 1;
                break;
            }
            BinaryTreeHelpQueue_enqueue(help_queue, current->right);
        }
        i++;
    }
    
    BinaryTreeHelpQueue_clean_without_free_node(&help_queue);
    tree->root = root;
    tree->node_num = array_len;

    if (build_abort) {
        BinaryTree_clean(&tree);
        return NULL;
    }
    return tree;
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

    BinaryTreeNode* node = _BinaryTreeNode_recursion_build_helper(
        in_order, pre_order, &pre_order_index, 0, in_len - 1,
        BINARY_TREE_BUILD_ORDER_INDEX_INCREASE
    );

    if (node == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        free(tree);
        return NULL;
    } else {
        tree->root = node;
        tree->node_num = in_len;
        return tree;
    }
}


BinaryTree* BinaryTree_build_of_post_order(
    BinaryTreeEleType* in_order, BinaryTreeEleType* post_order,
    size_t in_len, size_t post_len
) {
    if (in_order == NULL || post_order == NULL) {
        fprintf(stderr, BINARY_TREE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    BinaryTree* tree = BinaryTree_create(BINARY_TREE_INIT_DISABLE, NULL);
    if (tree == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        return NULL;
    }

    size_t post_order_index = post_len - 1;

    BinaryTreeNode* node = _BinaryTreeNode_recursion_build_helper(
        in_order, post_order, &post_order_index, 0, in_len - 1,
        BINARY_TREE_BUILD_ORDER_INDEX_DECREASE
    );

    if (node == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        free(tree);
        return NULL;
    } else {
        tree->root = node;
        tree->node_num = in_len;
        return tree;
    }
}


BinaryTree* BinaryTree_build_of_level_order(
    BinaryTreeEleType* in_order, BinaryTreeEleType* level_order,
    size_t in_len, size_t level_len
) {
    if (in_order == NULL || level_order == NULL) {
        fprintf(stderr, BINARY_TREE_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    BinaryTree* tree = BinaryTree_create(BINARY_TREE_INIT_DISABLE, NULL);
    if (tree == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        return NULL;
    }

    BinaryTreeNode* root = BinaryTreeNode_create(level_order[0]);
    if (root ==  NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        free(tree);
        return NULL;
    }

    root->left = root->right = NULL;

    BinaryTreeHelpQueue* help_queue = BinaryTreeHelpQueue_create();
    if (help_queue == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        BinaryTree_clean(&tree);
        BinaryTreeNode_clean(&root);
        return NULL;
    }

    BinaryTreeHelpQueue_enqueue(help_queue, root);

    size_t level_index = 1;

    int build_abort = 0;

    while (
        !BinaryTreeHelpQueue_is_empty(help_queue) && 
        level_index < level_len
    ) {
        BinaryTreeNode* current = BinaryTreeHelpQueue_dequeue(help_queue);

        ssize_t in_order_index = BinaryTree_in_order_index_search(
            in_order, 0, in_len - 1, current->data
        );

        if (in_order_index == -1) continue;

        if (level_index < level_len) {
            BinaryTreeEleType left_node_data = level_order[level_index];
            ssize_t left_index = BinaryTree_in_order_index_search(
                in_order, 0, in_order_index - 1, left_node_data
            );

            if (left_index != -1) {
                BinaryTreeNode* left_node = BinaryTreeNode_create(left_node_data);
                if (left_node ==  NULL) {
                    fprintf(stderr, BINARY_TREE_BUILD_ERROR);
                    build_abort = 1;
                    break;
                }

                left_node->left = left_node->right = NULL;
                current->left = left_node;
                BinaryTreeHelpQueue_enqueue(help_queue, left_node);
                level_index++;
            }

            if (level_index < level_len) {
                BinaryTreeEleType right_node_data = level_order[level_index];

                ssize_t right_index = BinaryTree_in_order_index_search(
                    in_order, in_order_index + 1, in_len - 1, right_node_data
                );

                if (right_index != -1) {
                    BinaryTreeNode* right_node = BinaryTreeNode_create(right_node_data);
                    if (right_node ==  NULL) {
                        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
                        build_abort = 1;
                        break;
                    }
                    right_node->left = right_node->right = NULL;
                    current->right = right_node;
                    BinaryTreeHelpQueue_enqueue(help_queue, right_node);
                    level_index++;
                }
            }
        }
    }

    BinaryTreeHelpQueue_clean_without_free_node(&help_queue);

    tree->root = root;
    tree->node_num = in_len;

    if (build_abort) {
        BinaryTree_clean(&tree);
        return NULL;
    }

    return tree;
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


BinaryTreeNode* _BinaryTreeNode_recursion_build_helper(
    BinaryTreeEleType* in_order, BinaryTreeEleType* help_order, 
    size_t* help_order_index, size_t in_order_start, size_t in_order_end,
    BinaryTreeBuildHelpOrderIndexModeEnum mode
) {
    if (in_order_start > in_order_end) {
        return NULL;
    }

    BinaryTreeNode* node = 
        BinaryTreeNode_create(help_order[*help_order_index]);
    if (node == NULL) {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        return NULL;
    }

    if (mode == BINARY_TREE_BUILD_ORDER_INDEX_INCREASE) {
        (*help_order_index)++;
    } else if (mode == BINARY_TREE_BUILD_ORDER_INDEX_DECREASE) {
        (*help_order_index)--;
    } else {
        fprintf(stderr, BINARY_TREE_BUILD_ERROR);
        return NULL;
    }

    if (in_order_start == in_order_end) {
        return node;
    }

    ssize_t in_index = BinaryTree_in_order_index_search(
        in_order, in_order_start, in_order_end, node->data
    );

    if (mode == BINARY_TREE_BUILD_ORDER_INDEX_INCREASE) {
        node->left = _BinaryTreeNode_recursion_build_helper(
            in_order, help_order, help_order_index, in_order_start, in_index - 1, mode
        );

        node->right = _BinaryTreeNode_recursion_build_helper(
            in_order, help_order, help_order_index, in_index + 1, in_order_end, mode
        );
    } else if (mode == BINARY_TREE_BUILD_ORDER_INDEX_DECREASE) {
        node->right = _BinaryTreeNode_recursion_build_helper(
            in_order, help_order, help_order_index, in_index + 1, in_order_end, mode
        );

        node->left = _BinaryTreeNode_recursion_build_helper(
            in_order, help_order, help_order_index, in_order_start, in_index - 1, mode
        );
    }

    return node;
}


BinaryTreeNode* _BinaryTreeNode_recursion_copy_helper(BinaryTreeNode* node) {
    if (node == NULL) {
        return NULL;
    }

    BinaryTreeNode* new_node = BinaryTreeNode_create(node->data);
    if (new_node == NULL) {
        fprintf(stderr, BINARY_TREE_COPY_ERROR);
        return NULL;
    }

    new_node->left = _BinaryTreeNode_recursion_copy_helper(node->left);
    new_node->right = _BinaryTreeNode_recursion_copy_helper(node->right);

    return new_node;
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


int BinaryTree_collect_handler(BinaryTreeNode* node, BinaryTreeContext* q) {
    if (node == NULL) {
        fprintf(stderr, BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    BinaryTreeHelpQueue_enqueue((BinaryTreeHelpQueue*) q, node);
    return 0;
}


int BinaryTree_clean_handler(BinaryTreeNode* node,  BinaryTreeContext* ctx) {
    if (node == NULL) {
        fprintf(stderr, BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    BinaryTreeNode_clean(&node);
    return 0;
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


int BinaryTreeNode_display(BinaryTreeNode* node) {
    if (node == NULL) {
        fprintf(stderr, BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    printf("%d  ", node->data);
    return 0;
}


BinaryTreeHelpQueue* BinaryTreeHelpQueue_create() {
    BinaryTreeHelpQueue* q = 
        (BinaryTreeHelpQueue*)malloc(sizeof(BinaryTreeHelpQueue));

    if (q == NULL) {
        fprintf(stderr, BINARY_TREE_HELP_QUEUE_CREATE_ERROR);
        return NULL;
    }

    q->front = q->rear = NULL;
    return q;
}


int BinaryTreeHelpQueue_enqueue(
    BinaryTreeHelpQueue* q, BinaryTreeNode* tree_node
) {
    if (q == NULL) {
        fprintf(stderr, BINARY_TREE_HELP_QUEUE_ACCESS_EXCEPTION);
        return -1;
    }

    BinaryTreeHelpQueueNode* new_node = 
        (BinaryTreeHelpQueueNode*) 
        malloc (sizeof(BinaryTreeHelpQueueNode));
    
    if (q == NULL) {
        fprintf(stderr, BINARY_TREE_HELP_QUEUE_NODE_CREATE_ERROR);
        return -1;
    }

    new_node->tree_node = tree_node;
    new_node->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }

    return 0;
}


BinaryTreeNode* BinaryTreeHelpQueue_dequeue(BinaryTreeHelpQueue* q) {
    if (q == NULL) {
        fprintf(stderr, BINARY_TREE_HELP_QUEUE_ACCESS_EXCEPTION);
        return NULL;
    }

    if (q->front == NULL) return NULL;
    
    BinaryTreeHelpQueueNode* temp = q->front;
    BinaryTreeNode* tree_node = temp->tree_node;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return tree_node;
}


int BinaryTreeHelpQueue_is_empty(BinaryTreeHelpQueue* q) {
    return q->front == NULL;
}


int BinaryTreeHelpQueue_clean_without_free_node(BinaryTreeHelpQueue** q) {
    if (q == NULL || *q == NULL) {
        fprintf(stderr, BINARY_TREE_HELP_QUEUE_ACCESS_EXCEPTION);
        return -1;
    }

    while (!BinaryTreeHelpQueue_is_empty(*q)) {
        BinaryTreeHelpQueue_dequeue(*q);
    }

    free(*q);
    *q = NULL;

    return 0;
}
