#include "singlelinkedlist.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {

    SingleLinkedList* list = singlelinkedlist_create(10);

    singlelinkedlist_push_back(list, 2333);
    singlelinkedlist_push_back(list, 23333);
    singlelinkedlist_push_back(list, 233333);
    singlelinkedlist_display(list);

    singlelinkedlist_push_front(list, 23);
    singlelinkedlist_display(list); 


    singlelinkedlist_insert(list, 233, 1);
    singlelinkedlist_display(list); 

    singlelinkedlist_insert(list, 233, list->length);
    singlelinkedlist_display(list); 

    singlelinkedlist_insert(list, 233, 3);
    singlelinkedlist_display(list); 


    singlelinkedlist_remove(list, 5);
    singlelinkedlist_display(list);

    SingleLinkedListEleType ele;
    singlelinkedlist_pop_front(list, &ele);
    printf("Popped from front: %d\n", ele);
    singlelinkedlist_display(list);

    singlelinkedlist_pop_back(list, &ele);
    printf("Popped from back: %d\n", ele);
    singlelinkedlist_display(list);

    singlelinkedlist_front(list, &ele);
    printf("Front element: %d\n", ele);

    singlelinkedlist_back(list, &ele);
    printf("Back element: %d\n", ele);

    SingleLinkedListEleType search_buf = 233;
    size_t search_pos = 3;
    int result = singlelinkedlist_search(list, &search_buf, &search_pos, -1);

    if (result == 0) {
        printf("Found element %d at position %zu\n", search_buf, search_pos);
    } else {
        printf("Element not found.\n");
    }

    singlelinkedlist_clean(&list);

    return 0;
}
