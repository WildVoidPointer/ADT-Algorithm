#include "tree_utils/tree_utils.h"


struct TraverseHelpStack {
    TreeNode** nodes;
    int length;
    int size;
};


static struct TraverseHelpStack* stack_create(int size) {
    struct TraverseHelpStack* st = 
        (struct TraverseHelpStack*) malloc (sizeof(struct TraverseHelpStack));

    if (st == NULL) {
        return NULL;
    }

    st->nodes = (TreeNode**) malloc (size * sizeof(TreeNode*));
    if (st->nodes == NULL) {
        free(st);
        return NULL;
    }

    st->length = 0;
    st->size = size;
    return st;
}


static int stack_is_empty(struct TraverseHelpStack* st) {
    return st->length <= 0;
}


static int stack_is_full(struct TraverseHelpStack* st) {
    return st->length >= st->size;
}


static int stack_push(struct TraverseHelpStack* st, TreeNode* node) {
    if (stack_is_full(st)) {
        return -1;
    }

    st->nodes[st->length++] = node;
    return 0;
}


static TreeNode* stack_pop(struct TraverseHelpStack* st) {
    if (stack_is_empty(st)) {
        return NULL;
    }

    TreeNode* buf = st->nodes[st->length - 1];
    st->length--;
    return buf;
}


static TreeNode* stack_peek(struct TraverseHelpStack* st) {
    if (stack_is_empty(st)) {
        return NULL;
    }
    return st->nodes[st->length - 1];
}


static int stack_destroy(struct TraverseHelpStack* st) {
    free(st->nodes);
    free(st);
    return 0;
}


static int binary_tree_pre_order_iterate_traverse(TreeNode* t, int st_size) {
    struct TraverseHelpStack* st = stack_create(st_size);

    if (st == NULL || t == NULL) {
        return -1;
    }

    stack_push(st, t);
    TreeNode* popped_node = NULL;

    while (!  stack_is_empty(st)) {
        popped_node = stack_pop(st);

        if (popped_node != NULL) {
            printf("%d  ", popped_node->data);
        }

        if (popped_node->right != NULL) {
            stack_push(st, popped_node->right);
        }

        if (popped_node->left != NULL) {
            stack_push(st, popped_node->left);
        }
    }

    printf("\n");

    stack_destroy(st);
}


static int binary_tree_in_order_iterate_traverse(TreeNode* t, int st_size){
     struct TraverseHelpStack* st = stack_create(st_size);

    if (st == NULL || t == NULL) {
        return -1;
    }

    TreeNode* curr = t;
    while (curr != NULL || ! stack_is_empty(st)) {
        // 一路向左，将所有左子节点压栈
        while (curr != NULL) {
            stack_push(st, curr);
            curr = curr->left;
        }
        
        // 弹出栈顶节点并访问
        curr = stack_pop(st);

        if (curr != NULL) {
            printf("%d  ", curr->data);
            // 转向右子树
            curr = curr->right;
        }
    }

    printf("\n");

    stack_destroy(st);
}


static int binary_tree_post_order_iterate_traverse(TreeNode* t, int st_size) {
    if (t == NULL) {
        return -1;
    }

    struct TraverseHelpStack* st1 = stack_create(st_size);
    struct TraverseHelpStack* st2 = stack_create(st_size);
    
    if (st1 == NULL || st2 == NULL) {
        if (st1) stack_destroy(st1);
        if (st2) stack_destroy(st2);
        return -1;
    }

    stack_push(st1, t);
    TreeNode* popped_node = NULL;

    // 第一个栈用于模拟类似前序的遍历（根->右->左）
    while (! stack_is_empty(st1)) {
        popped_node = stack_pop(st1);
        
        if (popped_node != NULL) {
            // 将节点压入第二个栈
            stack_push(st2, popped_node);
            
            // 注意：这里先左后右，与标准前序相反
            if (popped_node->left != NULL) {
                stack_push(st1, popped_node->left);
            }

            if (popped_node->right != NULL) {
                stack_push(st1, popped_node->right);
            }
        }
    }

    // 第二个栈出栈顺序就是后序遍历（左->右->根）
    while (! stack_is_empty(st2)) {
        popped_node = stack_pop(st2);

        if (popped_node != NULL) {
            printf("%d  ", popped_node->data);
        }
    }

    printf("\n");
    stack_destroy(st1);
    stack_destroy(st2);
    return 0;
}


static int binary_tree_post_order_iterate_single_stack(TreeNode* t, int st_size) {
    if (t == NULL) {
        return -1;
    }

    struct TraverseHelpStack* st = stack_create(st_size);
    if (st == NULL) {
        return -1;
    }

    TreeNode* current = t;
    TreeNode* last_visited = NULL;
    TreeNode* peeked_node = NULL;

    while (current != NULL || ! stack_is_empty(st)) {
        // 一路向左
        if (current != NULL) {
            stack_push(st, current);
            current = current->left;
        } else {
            peeked_node = stack_peek(st);
            
            // 如果右子树存在且未被访问过
            if (peeked_node->right != NULL && last_visited != peeked_node->right) {
                current = peeked_node->right;
            } else {
                // 访问节点
                printf("%d  ", peeked_node->data);
                last_visited = stack_pop(st);
            }
        }
    }

    printf("\n");
    stack_destroy(st);
    return 0;
}


int main() {
    TreeNode* tree = default_full_binary_tree_generate();

    if (tree != NULL) {
        binary_tree_pre_order_iterate_traverse(tree, 8);
    }

    if (tree != NULL) {
        binary_tree_in_order_iterate_traverse(tree, 8);
    }

    if (tree != NULL) {
        binary_tree_post_order_iterate_traverse(tree, 8);
    }
}
