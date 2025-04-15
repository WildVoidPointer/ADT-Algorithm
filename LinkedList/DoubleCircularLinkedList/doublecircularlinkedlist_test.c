#include "doublecircularlinkedlist.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
    // 创建容量为10的链表
    DoubleCircularLinkedList* list = doublecircularlinkedlist_create(10, 0);
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return -1;
    }

    // 测试尾插法
    doublecircularlinkedlist_push_back(list, 2333);
    doublecircularlinkedlist_push_back(list, 23333);
    doublecircularlinkedlist_push_back(list, 233333);
    printf("After push_back:\n");
    doublecircularlinkedlist_display(list);

    // 测试头插法
    doublecircularlinkedlist_push_front(list, 23);
    printf("\nAfter push_front:\n");
    doublecircularlinkedlist_display(list);

    // 测试插入
    doublecircularlinkedlist_insert(list, 233, 1);  // 插入到第一个位置
    printf("\nAfter insert at position 1:\n");
    doublecircularlinkedlist_display(list);

    doublecircularlinkedlist_insert(list, 233, list->length);  // 插入到末尾
    printf("\nAfter insert at last position:\n");
    doublecircularlinkedlist_display(list);

    doublecircularlinkedlist_insert(list, 233, 3);  // 插入到中间位置
    printf("\nAfter insert at position 3:\n");
    doublecircularlinkedlist_display(list);

    // 测试删除
    DoubleCircularLinkedListEleType remove_data;
    size_t remove_pos = 2;
    doublecircularlinkedlist_remove(list, &remove_data, &remove_pos, DOUBLECIRCULARLINKEDLIST_SEARCH_BY_POS);
    printf("\nAfter remove position 2 (removed data: %d):\n", remove_data);
    doublecircularlinkedlist_display(list);

    // 测试弹出
    DoubleCircularLinkedListEleType ele;
    doublecircularlinkedlist_pop_front(list, &ele);
    printf("\nPopped from front: %d\n", ele);
    doublecircularlinkedlist_display(list);

    doublecircularlinkedlist_pop_back(list, &ele);
    printf("\nPopped from back: %d\n", ele);
    doublecircularlinkedlist_display(list);

    // 测试查看头尾元素
    doublecircularlinkedlist_front(list, &ele);
    printf("\nFront element: %d\n", ele);

    doublecircularlinkedlist_back(list, &ele);
    printf("Back element: %d\n", ele);

    // 测试搜索
    DoubleCircularLinkedListEleType search_buf = 233;
    size_t search_pos = 0;
    int result = doublecircularlinkedlist_search(list, &search_buf, &search_pos, DOUBLECIRCULARLINKEDLIST_SEARCH_BY_VALUE);

    if (result == 0) {
        printf("\nFound element %d at position %zu\n", search_buf, search_pos);
    } else {
        printf("\nElement not found.\n");
    }

    // 测试按位置搜索
    search_pos = 2;
    result = doublecircularlinkedlist_search(list, &search_buf, &search_pos, DOUBLECIRCULARLINKEDLIST_SEARCH_BY_POS);
    if (result == 0) {
        printf("Element at position %zu: %d\n", search_pos, search_buf);
    } else {
        printf("Invalid position\n");
    }

    // 测试长度和容量
    printf("\nCurrent length: %zu\n", doublecircularlinkedlist_length(list));
    printf("Capacity: %zd\n", doublecircularlinkedlist_size(list));

    // 清理链表
    doublecircularlinkedlist_clean(&list);
    printf("\nAfter clean:\n");
    if (list == NULL) {
        printf("List is NULL (properly cleaned)\n");
    }

    return 0;
}