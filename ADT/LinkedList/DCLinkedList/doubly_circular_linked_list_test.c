#include "doubly_circular_linked_list.h"
#include <stdio.h>


int main(int argc, char const *argv[]) {
    // 创建容量为10的链表
    DCLinkedList* list = DCLinkedList_create(10, 0);
    if (list == NULL) {
        fprintf(stderr, "Failed to create list\n");
        return -1;
    }

    DCLinkedList_push_back(NULL, 123);

    // 测试尾插法
    DCLinkedList_push_back(list, 123);
    DCLinkedList_push_back(list, 223);
    DCLinkedList_push_back(list, 3233);
    printf("After push_back:\n");
    DCLinkedList_display(list);

    // 测试头插法
    DCLinkedList_push_front(list, 2330);
    printf("\nAfter push_front:\n");
    DCLinkedList_display(list);

    // 测试插入
    DCLinkedList_insert(list, 2331, 1);  // 插入到第一个位置
    printf("\nAfter insert at position 1:\n");
    DCLinkedList_display(list);

    DCLinkedList_insert(list, 233200, list->length);  // 插入到末尾
    printf("\nAfter insert at last position:\n");
    DCLinkedList_display(list);

    DCLinkedList_insert(list, 233400, 3);  // 插入到中间位置
    printf("\nAfter insert at position 3:\n");
    DCLinkedList_display(list);

    // 测试删除
    DCLinkedListDataType remove_data;
    size_t remove_pos = 2;
    DCLinkedList_remove(
        list, &remove_data, &remove_pos, DC_LINKED_LIST_SEARCH_BY_POS);

    printf("\nAfter remove position 2 (removed data: %d):\n", remove_data);
    DCLinkedList_display(list);

    // 测试弹出
    DCLinkedListDataType ele;
    DCLinkedList_pop_front(list, &ele);
    printf("\nPopped from front: %d\n", ele);
    DCLinkedList_display(list);

    DCLinkedList_pop_back(list, &ele);
    printf("\nPopped from back: %d\n", ele);
    DCLinkedList_display(list);

    // 测试查看头尾元素
    DCLinkedList_front(list, &ele);
    printf("\nFront element: %d\n", ele);

    DCLinkedList_back(list, &ele);
    printf("Back element: %d\n", ele);

    // 测试搜索
    DCLinkedListDataType search_buf = 233;
    size_t search_pos = 0;
    int result = DCLinkedList_search(
        list, &search_buf, &search_pos, DC_LINKED_LIST_SEARCH_BY_VALUE);

    if (result == 0) {
        printf("\nFound element %d at position %zu\n", search_buf, search_pos);
    } else {
        printf("\nElement not found.\n");
    }

    // 测试按位置搜索
    search_pos = 2;
    result = DCLinkedList_search(
        list, &search_buf, &search_pos, DC_LINKED_LIST_SEARCH_BY_POS);

    if (result == 0) {
        printf("Element at position %zu: %d\n", search_pos, search_buf);
    } else {
        printf("Invalid position\n");
    }

    // 测试长度和容量
    printf("\nCurrent length: %zu\n", DCLinkedList_length(list));
    printf("Capacity: %zd\n", DCLinkedList_size(list));

    // 清理链表
    DCLinkedList_destroy(&list);
    printf("\nAfter clean:\n");
    if (list == NULL) {
        printf("List is NULL (properly cleaned)\n");
    }

    return 0;
}