#include "single_linked_list.h"
#include <stdio.h>


int main(int argc, char const *argv[]) {

    SingleLinkedListEleType ele;
    SingleLinkedList* list = SingleLinkedList_create(5);

    SingleLinkedList_push_back(list, 2333);
    SingleLinkedList_push_back(list, 23333);
    SingleLinkedList_push_back(list, 23);
    SingleLinkedList_display(list);

    SingleLinkedList_push_front(list, 23);
    SingleLinkedList_display(list); 

    SingleLinkedList_insert(list, 1233, 1);
    SingleLinkedList_display(list);

    SingleLinkedList_insert(list, 233, list->length + 1);
    SingleLinkedList_display(list); 

    SingleLinkedList_pop_front(list, &ele);
    printf("Popped from front: %d\n", ele);
    SingleLinkedList_display(list);

    SingleLinkedList_reverse(list);
    SingleLinkedList_display(list);

    SingleLinkedList_pop_back(list, &ele);
    printf("Popped from back: %d\n", ele);
    SingleLinkedList_display(list);

    SingleLinkedList_insert(list, 3233, 3);
    SingleLinkedList_display(list); 

    SingleLinkedList_remove(list, &ele, 5, SINGLELINKEDLIST_SEARCH_BY_POS);
    SingleLinkedList_display(list);

    SingleLinkedList_remove(list, &ele, 1, SINGLELINKEDLIST_SEARCH_BY_POS);
    SingleLinkedList_display(list);

    SingleLinkedList_front(list, &ele);
    printf("Front element: %d\n", ele);

    SingleLinkedList_back(list, &ele);
    printf("Back element: %d\n", ele);

    SingleLinkedListEleType search_buf = 3233;
    size_t search_pos = 3;

    int result = SingleLinkedList_search(list, &search_buf, &search_pos, SINGLELINKEDLIST_SEARCH_BY_VALUE);
    if (result == 0) {
        printf("Found element %d at position %zu\n", search_buf, search_pos);
    } else {
        printf("Element not found.\n");
    }


    result = SingleLinkedList_search(list, &search_buf, &search_pos, SINGLELINKEDLIST_SEARCH_BY_VALUE);
    if (result == 0) {
        printf("Found element %d at position %zu\n", search_buf, search_pos);
    } else {
        printf("Element not found.\n");
    }

    SingleLinkedList_clean(&list);

    return 0;
}
