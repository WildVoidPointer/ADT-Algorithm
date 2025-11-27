#include "singly_linked_list.h"
#include <stdio.h>


int main(int argc, char const *argv[]) {

    SLinkedListDataType ele;
    SLinkedList* list = SLinkedList_create(5);

    SLinkedList_push_back(list, 2333);
    SLinkedList_push_back(list, 23333);
    SLinkedList_push_back(list, 23);
    SLinkedList_display(list);

    SLinkedList_push_front(list, 23);
    SLinkedList_display(list); 

    SLinkedList_insert(list, 1233, 1);
    SLinkedList_display(list);

    SLinkedList_insert(list, 233, list->length + 1);
    SLinkedList_display(list); 

    SLinkedList_pop_front(list, &ele);
    printf("Popped from front: %d\n", ele);
    SLinkedList_display(list);

    SLinkedList_reverse(list);
    SLinkedList_display(list);

    SLinkedList_recursion_reverse(list);
    SLinkedList_display(list);

    SLinkedList_pop_back(list, &ele);
    printf("Popped from back: %d\n", ele);
    SLinkedList_display(list);

    SLinkedList_insert(list, 3233, 3);
    SLinkedList_display(list); 

    SLinkedList_remove(list, &ele, 5, S_LINKED_LIST_SEARCH_BY_POS);
    SLinkedList_display(list);

    SLinkedList_remove(list, &ele, 1, S_LINKED_LIST_SEARCH_BY_POS);
    SLinkedList_display(list);

    SLinkedList_front(list, &ele);
    printf("Front element: %d\n", ele);

    SLinkedList_back(list, &ele);
    printf("Back element: %d\n", ele);

    SLinkedListDataType search_buf = 3233;
    size_t search_pos = 3;

    int result = SLinkedList_search(
        list, &search_buf, &search_pos, S_LINKED_LIST_SEARCH_BY_VALUE
    );

    if (result == 0) {
        printf(
            "Found element %d at position %zu\n", 
            search_buf, 
            search_pos
        );

    } else {
        printf("Element not found.\n");
    }


    result = SLinkedList_search(
        list, &search_buf, &search_pos, S_LINKED_LIST_SEARCH_BY_VALUE
    );
    
    if (result == 0) {
        printf(
            "Found element %d at position %zu\n", 
            search_buf, 
            search_pos
        );
    } else {
        printf("Element not found.\n");
    }

    SLinkedList_clean(&list);

    return 0;
}
