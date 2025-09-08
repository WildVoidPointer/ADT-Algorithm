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
    tree->is_threaded = THREAD_BINARY_TREE_IS_NOT_THREADED;
    return tree;
}


int ThreadBinaryTree_display(
    ThreadBinaryTree* th_tree, ThreadBinaryTreeTraverser th_traverser
) {
    if (th_tree == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    if (th_traverser != NULL) {
        printf("ThreadBinaryTree: {  ");
        th_traverser(
            th_tree->root,
            ThreadBinaryTree_display_handler,
            NULL
        );
        printf("}\n");
    }
}


int ThreadBinaryTree_clean(ThreadBinaryTree** th_tree) {
    if (th_tree == NULL || *th_tree == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    if ((*th_tree)->is_threaded) {

    } else {
        ThreadBinaryTree_post_order_traverse(
            (*th_tree)->root,
            ThreadBinaryTree_clean_handler,
            NULL
        );
    }

    *th_tree = NULL;

    return 0;
}


ThreadBinaryTree* 
ThreadBinaryTree_build_of_binary_tree(BinaryTree* bin_tree) {
    if (bin_tree == NULL) {
        fprintf(stderr, BINARY_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    ThreadBinaryTree* th_tree = ThreadBinaryTree_create();

    if (th_tree == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_BUILD_ERROR);
        return NULL;
    }

    ThreadBinaryTreeNode* th_tree_root = 
        _ThreadBinaryTree_build_of_binary_tree_helper(bin_tree->root);

    if (th_tree_root == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_BUILD_ERROR);
        ThreadBinaryTree_clean(&th_tree);
        return NULL;
    }

    th_tree->node_num = bin_tree->node_num;
    th_tree->root = th_tree_root;

    return th_tree;
}


int ThreadBinaryTree_threading(
    ThreadBinaryTree* th_tree, ThreadBinaryTreeTraverser th_traverser
) {
    if (th_tree == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_ACCESS_EXCEPTION);
        return -1;
    }

    if (th_traverser == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_THREAD_TRAVERSER_ERROR);
        return -1;
    }

    ThreadBinaryTreeThreadingContext ctx = 
        (ThreadBinaryTreeThreadingContext){ .prev = NULL };
    
    int handle_re_code = th_traverser(
        th_tree->root, 
        ThreadBinaryTree_threading_handler, 
        (ThreadBinaryTreeHandleContext*)&ctx
    );

    if (handle_re_code == 0) {
        th_tree->is_threaded = 1;
        return 0;
    } else {
        return -1;
    }
}


ThreadBinaryTreeNode* ThreadBinaryTree_threaded_root(ThreadBinaryTree* th_tree) {
    if (th_tree == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_ACCESS_EXCEPTION);
        return NULL;
    }

    ThreadBinaryTreeNode* curr_node = th_tree->root;

    if (th_tree->is_threaded) {
        while (
            curr_node->left_is_prec == 
                THREAD_BINARY_TREE_LEFT_IS_NOT_PRECURSOR
        ) {
            curr_node = curr_node->left;
        }

        return curr_node;
    } else {
        fprintf(stderr, THREAD_BINARY_TREE_NOT_THREADED_EXCEPTION);
        return NULL;
    }
}


int ThreadBinaryTree_pre_order_traverse(
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandler th_handler, 
    ThreadBinaryTreeHandleContext* th_ctx
) {
    if (th_node != NULL && th_handler != NULL) {
        ThreadBinaryTreeNode* th_left = th_node->left;
        ThreadBinaryTreeNode* th_right = th_node->right;
        th_handler(th_node, th_ctx);
        ThreadBinaryTree_pre_order_traverse(th_left, th_handler, th_ctx);
        ThreadBinaryTree_pre_order_traverse(th_right, th_handler, th_ctx);
        return 0;
    } else {
        return -1;
    }
}


int ThreadBinaryTree_in_order_traverse(
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandler th_handler, 
    ThreadBinaryTreeHandleContext* th_ctx
) {
    if (th_node != NULL && th_handler != NULL) {
        ThreadBinaryTree_in_order_traverse(th_node->left, th_handler, th_ctx);
        th_handler(th_node, th_ctx);
        ThreadBinaryTree_in_order_traverse(th_node->right, th_handler, th_ctx);
        return 0;
    } else {
        return -1;
    }
}


int ThreadBinaryTree_post_order_traverse(
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandler th_handler, 
    ThreadBinaryTreeHandleContext* th_ctx
) {
    if (th_node != NULL && th_handler != NULL) {
        ThreadBinaryTree_post_order_traverse(th_node->left, th_handler, th_ctx);
        ThreadBinaryTree_post_order_traverse(th_node->right, th_handler, th_ctx);
        th_handler(th_node, th_ctx);
        return 0;
    } else {
        return -1;
    }
}


int ThreadBinaryTree_pre_order_threaded_traverse(
    ThreadBinaryTreeNode* th_root, ThreadBinaryTreeHandler th_handler, 
    ThreadBinaryTreeHandleContext* th_ctx
) {
    if (th_root == NULL || th_handler == NULL) {
        return -1;
    }
    
    ThreadBinaryTreeNode* curr = th_root;

    while (curr != NULL) {
        th_handler(curr, th_ctx);

        if (curr->left_is_prec == THREAD_BINARY_TREE_LEFT_IS_NOT_PRECURSOR) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return 0;
}


int ThreadBinaryTree_in_order_threaded_traverse(
    ThreadBinaryTreeNode* th_root, ThreadBinaryTreeHandler th_handler, 
    ThreadBinaryTreeHandleContext* th_ctx
) {
    if (th_root == NULL || th_handler == NULL) {
        return -1;
    }
    
    ThreadBinaryTreeNode* curr = th_root;
    
    // 找到中序遍历的第一个节点（最左边的节点）
    while (
        curr->left != NULL &&
        curr->left_is_prec == THREAD_BINARY_TREE_LEFT_IS_NOT_PRECURSOR
    ) {
        curr = curr->left;
    }
    
    while (curr != NULL) {
        // 处理当前节点
        th_handler(curr, th_ctx);
        
        // 如果右指针是线索，直接跟随
        if (curr->right_is_succ == THREAD_BINARY_TREE_RIGHT_IS_SUCCESSOR) {
            curr = curr->right;
        } else {
            // 否则，转到右子树，然后找到右子树的最左节点
            curr = curr->right;
            if (curr != NULL) {
                while (
                    curr->left != NULL && 
                    curr->left_is_prec == THREAD_BINARY_TREE_LEFT_IS_NOT_PRECURSOR
                ) {
                    curr = curr->left;
                }
            }
        }
    }
    
    return 0;
}


int ThreadBinaryTree_threading_handler(
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandleContext* th_ctx
) {
    if (th_node == NULL) {
        return -1;
    }

    ThreadBinaryTreeThreadingContext* ctx = (ThreadBinaryTreeThreadingContext*)th_ctx;
    
    // 处理左线索
    if (th_node->left == NULL) {
        th_node->left = ctx->prev;
        th_node->left_is_prec = THREAD_BINARY_TREE_LEFT_IS_PRECURSOR;
    } else {
        th_node->left_is_prec = THREAD_BINARY_TREE_LEFT_IS_NOT_PRECURSOR;
    }
    
    // 处理前驱节点的右线索
    if (ctx->prev != NULL && ctx->prev->right == NULL) {
        ctx->prev->right = th_node;
        ctx->prev->right_is_succ = THREAD_BINARY_TREE_RIGHT_IS_SUCCESSOR;
    } else if (ctx->prev != NULL) {
        ctx->prev->right_is_succ = THREAD_BINARY_TREE_RIGHT_IS_NOT_SUCCESSOR;
    }
    
    // 更新前驱节点
    ctx->prev = th_node;
    
    return 0;
}


int ThreadBinaryTree_display_handler(
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandleContext* ctx
) {
    if (th_node == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    printf("%d  ", th_node->data);
    return 0;
}


int ThreadBinaryTree_clean_handler(
    ThreadBinaryTreeNode* th_node, ThreadBinaryTreeHandleContext* ctx
) {
    if (th_node == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    ThreadBinaryTreeNode_clean(&th_node);
    return 0;
}


ThreadBinaryTreeNode*
_ThreadBinaryTree_build_of_binary_tree_helper(BinaryTreeNode* bin_node) {
    if (bin_node == NULL) {
        return NULL;
    }

    ThreadBinaryTreeNode* new_th_node = ThreadBinaryTreeNode_create(bin_node->data);

    if (new_th_node == NULL) {
        return NULL;
    }

    new_th_node->left_is_prec = THREAD_BINARY_TREE_LEFT_IS_NOT_PRECURSOR;
    new_th_node->right_is_succ = THREAD_BINARY_TREE_RIGHT_IS_NOT_SUCCESSOR;

    new_th_node->left = _ThreadBinaryTree_build_of_binary_tree_helper(bin_node->left);
    new_th_node->right = _ThreadBinaryTree_build_of_binary_tree_helper(bin_node->right);

    return new_th_node;
}


ThreadBinaryTreeNode* 
ThreadBinaryTreeNode_create(ThreadBinaryTreeEleType data) {
    ThreadBinaryTreeNode* th_node = 
        (ThreadBinaryTreeNode*) malloc (sizeof(ThreadBinaryTreeNode));

    if (th_node == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_NODE_CREATE_ERROR);
        return NULL;
    }

    th_node->data = data;
    th_node->left = th_node->right = NULL;

    return th_node;
}


int ThreadBinaryTreeNode_clean(ThreadBinaryTreeNode** th_node) {
    if (*th_node == NULL || th_node == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    free(*th_node);
    *th_node = NULL;
    return 0;
}


int ThreadBinaryTreeNode_display(ThreadBinaryTreeNode* th_node) {
    if (th_node == NULL) {
        fprintf(stderr, THREAD_BINARY_TREE_NODE_ACCESS_EXCEPTION);
        return -1;
    }

    printf(
        "ThreadBinaryTreeNode: {  data = %d  left_state = %d  right_state = %d}\n",
        th_node->data,
        th_node->left_is_prec,
        th_node->right_is_succ
    );

    return 0;
}
