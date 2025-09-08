#include "binary_tree.h"


void BinaryTreeEleType_array_println(char* desp, int len, BinaryTreeEleType* order) {
    printf("%s: {  ", desp);
    for (int i = 0; i < len; i++) {
        printf("%d  ", order[i]);
    }
    printf("}\n");
}


int main() {
    BinaryTreeEleType tree_node_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int tree_node_array_len = 
        sizeof(tree_node_array) / sizeof(tree_node_array[0]);


    BinaryTreeEleType level_order[] = {1, 2, 3, -1, 4, 5, 6};
    BinaryTreeEleType pre_order[] = {1, 2, -1, 4, 3, 5, 6};
    BinaryTreeEleType in_order[] = {-1, 2, 4, 1, 5, 3, 6};
    BinaryTreeEleType post_order[] = {-1, 4, 2, 5, 6, 3, 1};
    int order_len = sizeof(level_order) / sizeof(level_order[0]);

    
    BinaryTree* tree = BinaryTree_build_of_array(
        tree_node_array, tree_node_array_len
    );

    BinaryTreeEleType_array_println(
        "OriginArrayInfo", 
        tree_node_array_len, tree_node_array
    );
    printf("BinaryTreeBuildLevelOrderResult: ");
    BinaryTree_display(tree, NULL);

    printf("BinaryTreeArrayBuildPreOrderResult: ");
    BinaryTree_display(tree, BinaryTree_pre_order_traverse);

    printf("BinaryTreeArrayBuildInOrderResult: ");
    BinaryTree_display(tree, BinaryTree_in_order_traverse);

    printf("BinaryTreeArrayBuildPostOrderResult: ");
    BinaryTree_display(tree, BinaryTree_post_order_traverse);

    BinaryTree_clean(&tree);
    printf("BinaryTreeArrayBuildCleanResult: %p\n", tree);
    printf("=======================\n");


    BinaryTree* origin_tree = BinaryTree_build_of_array(
        tree_node_array, tree_node_array_len
    );
    BinaryTree* copied_tree = BinaryTree_copy(origin_tree);

    printf("OriginBinaryTree: ");
    BinaryTree_display(origin_tree, NULL);

    printf("CopiedBinaryTree: ");
    BinaryTree_display(copied_tree, NULL);

    BinaryTree_clean(&copied_tree);
    BinaryTree_clean(&origin_tree);
    printf("=======================\n");


    BinaryTree* pre_order_build_res = BinaryTree_build_of_pre_order(
        in_order, pre_order, order_len, order_len
    );
    BinaryTreeEleType_array_println("LevelOrder", order_len, level_order);
    BinaryTree_display(pre_order_build_res, NULL);

    BinaryTreeEleType_array_println("PreOrder  ", order_len, pre_order);
    BinaryTree_display(pre_order_build_res, BinaryTree_pre_order_traverse);

    BinaryTreeEleType_array_println("InOrder   ", order_len, in_order);
    BinaryTree_display(pre_order_build_res, BinaryTree_in_order_traverse);

    BinaryTreeEleType_array_println("PostOrder ", order_len, post_order);
    BinaryTree_display(pre_order_build_res, BinaryTree_post_order_traverse);

    BinaryTree_clean(&pre_order_build_res);
    printf("=======================\n");


    BinaryTree* post_order_build_res = BinaryTree_build_of_post_order(
        in_order, post_order, order_len, order_len
    );
    BinaryTreeEleType_array_println("LevelOrder", order_len, level_order);
    BinaryTree_display(post_order_build_res, NULL);

    BinaryTreeEleType_array_println("PreOrder  ", order_len, pre_order);
    BinaryTree_display(post_order_build_res, BinaryTree_pre_order_traverse);

    BinaryTreeEleType_array_println("InOrder   ", order_len, in_order);
    BinaryTree_display(post_order_build_res, BinaryTree_in_order_traverse);

    BinaryTreeEleType_array_println("PostOrder ", order_len, post_order);
    BinaryTree_display(post_order_build_res, BinaryTree_post_order_traverse);

    BinaryTree_clean(&post_order_build_res);
    printf("=======================\n");


    BinaryTree* level_order_build_res = BinaryTree_build_of_level_order(
        in_order, level_order, order_len, order_len
    );
    BinaryTreeEleType_array_println("LevelOrder", order_len, level_order);
    BinaryTree_display(level_order_build_res, NULL);

    BinaryTreeEleType_array_println("PreOrder  ", order_len, pre_order);
    BinaryTree_display(level_order_build_res, BinaryTree_pre_order_traverse);

    BinaryTreeEleType_array_println("InOrder   ", order_len, in_order);
    BinaryTree_display(level_order_build_res, BinaryTree_in_order_traverse);

    BinaryTreeEleType_array_println("PostOrder ", order_len, post_order);
    BinaryTree_display(level_order_build_res, BinaryTree_post_order_traverse);
    
    printf("=======================\n");

    return 0;
}
