#include "doublecircularlinkedlist.h"


DoubleCircularLinkedList* doublecircularlinkedlist_create(ssize_t size){
    DoubleCircularLinkedList* list = (DoubleCircularLinkedList*)malloc(sizeof(DoubleCircularLinkedList));
    if (list == NULL) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_INIT_ERROR);
        return NULL;
    }
    list->length = 0;
    list->size = size;
    return list;
}


size_t doublecircularlinkedlist_length(DoubleCircularLinkedList* list){
    return list->length;
}


ssize_t doublecircularlinkedlist_size(DoubleCircularLinkedList* list){
    return list->size;
}


int _doublecircularlinkedlist_is_exceed_size(DoubleCircularLinkedList* list){
    return ((list->size != -1)
        && (list->length + 1 > list->size)) ? 1 : 0;
}


int doublecircularlinkedlist_push_front(DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType data);


int doublecircularlinkedlist_push_back(DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType data);


int
doublecircularlinkedlist_insert(DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType data, size_t pos);


int doublecircularlinkedlist_pop_front(DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data) {
    if (list == NULL) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (list->length == 0) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    DoubleCircularLinkedListNode* node = list->head;
    *data = list->head->data;
    list->head = list->head->next;
    list->length--;
    free(node);
    return 0;
}


int doublecircularlinkedlist_pop_back(DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data) {
    if (list == NULL) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (list->length == 0) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    DoubleCircularLinkedListNode* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    *data = current->next->data;
    free(current->next);
    current->next = NULL;
}


int doublecircularlinkedlist_remove(DoubleCircularLinkedList* list, size_t pos);


int doublecircularlinkedlist_front(DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_CHECK_ERROR);
        return -1;
    }
    *data = list->head->data;
    return 0;
}


int doublecircularlinkedlist_back(DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_CHECK_ERROR);
        return -1;
    }
    
    DoubleCircularLinkedListNode* current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }
    *data = current->data;
    return 0;
}


int 
doublecircularlinkedlist_search(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data, size_t* pos, int flag) {

    if (list == NULL) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (flag == 0 && (*pos > list->length || *pos <= 0)) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_SEARCH_EXCEPTION);
        return -1;
    }

    if (flag == 0) {
        DoubleCircularLinkedListNode* current = list->head;
        size_t count = 1;

        while ((current != NULL) && (count < *pos)) {
            current = current->next;
            count++;
        }
        *data = current->data;
    }
    else if (flag == -1) {
        DoubleCircularLinkedListNode* current = list->head;
        size_t count = 1;
        int search_state = 0;

        while (current != NULL) {
            if (current->data == *data) {
                search_state = 1;
                *pos = count;
                break;
            }
            current = current->next;
            count++;
        }

        if (search_state == 0) {
            fprintf(stderr, DOUBLECIRCULARLINKEDLIST_SEARCH_EXCEPTION);
            return -1;
        }
    }

    else {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_SEARCH_MODE_ERROR);
        return -1;
    }

    return 0;
}


int doublecircularlinkedlist_display(DoubleCircularLinkedList* list){
    if (list == NULL) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    DoubleCircularLinkedListNode* current = list->head;
    printf("DoubleCircularLinkedList: {  ");
    while (current != NULL) {
        printf("%d  ", current->data);
        current = current->next;
    }
    printf("}  length: %zu  size: %zd\n", list->length, list->size);
    return 0;
}


int doublecircularlinkedlist_clean(DoubleCircularLinkedList** list){
    if (list == NULL) {
        fprintf(stderr, DOUBLECIRCULARLINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    DoubleCircularLinkedListNode* current = (*list)->head;
    while (current != NULL) {
        DoubleCircularLinkedList* old = current;
        current = current->next;
        free(old);
    }
    free(*list);
    (*list) = NULL;
    return 0;
}
