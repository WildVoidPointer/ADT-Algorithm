#include "singlelinkedlist.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {

    SingleLinkedListEleType ele;
    SingleLinkedList* list = singlelinkedlist_create(5);

    singlelinkedlist_push_back(list, 2333);
    singlelinkedlist_push_back(list, 23333);
    singlelinkedlist_push_back(list, 23);
    singlelinkedlist_display(list);

    singlelinkedlist_push_front(list, 23);
    singlelinkedlist_display(list); 

    singlelinkedlist_insert(list, 1233, 1);
    singlelinkedlist_display(list);

    singlelinkedlist_insert(list, 233, list->length + 1);
    singlelinkedlist_display(list); 

    singlelinkedlist_pop_front(list, &ele);
    printf("Popped from front: %d\n", ele);
    singlelinkedlist_display(list);

    singlelinkedlist_pop_back(list, &ele);
    printf("Popped from back: %d\n", ele);
    singlelinkedlist_display(list);

    singlelinkedlist_insert(list, 3233, 3);
    singlelinkedlist_display(list); 

    singlelinkedlist_remove(list, &ele, 5, SINGLELINKEDLIST_SEARCH_BY_POS);
    singlelinkedlist_display(list);

    singlelinkedlist_remove(list, &ele, 1, SINGLELINKEDLIST_SEARCH_BY_POS);
    singlelinkedlist_display(list);

    singlelinkedlist_front(list, &ele);
    printf("Front element: %d\n", ele);

    singlelinkedlist_back(list, &ele);
    printf("Back element: %d\n", ele);

    SingleLinkedListEleType search_buf = 3233;
    size_t search_pos = 3;

    int result = singlelinkedlist_search(list, &search_buf, &search_pos, SINGLELINKEDLIST_SEARCH_BY_VALUE);
    if (result == 0) {
        printf("Found element %d at position %zu\n", search_buf, search_pos);
    } else {
        printf("Element not found.\n");
    }


    result = singlelinkedlist_search(list, &search_buf, &search_pos, SINGLELINKEDLIST_SEARCH_BY_VALUE);
    if (result == 0) {
        printf("Found element %d at position %zu\n", search_buf, search_pos);
    } else {
        printf("Element not found.\n");
    }

    singlelinkedlist_clean(&list);

    return 0;
}
