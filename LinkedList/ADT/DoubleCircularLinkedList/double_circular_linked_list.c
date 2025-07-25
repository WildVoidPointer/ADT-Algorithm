#include "double_circular_linked_list.h"


DoubleCircularLinkedList* 
DoubleCircularLinkedList_create(ssize_t size, DoubleCircularLinkedListEleType init_data) {
    DoubleCircularLinkedList* list = (DoubleCircularLinkedList*) 
                                    malloc(sizeof(DoubleCircularLinkedList));
    if (list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_INIT_ERROR);
        return NULL;
    }

    DoubleCircularLinkedListNode* node = 
        (DoubleCircularLinkedListNode*) malloc (sizeof(DoubleCircularLinkedListNode));

    if (node == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_NODE_INIT_ERROR);
        free(list);
        return NULL;
    }

    node->data = init_data;
    node->next = node;
    node->prev = node;
    list->head = node;
    list->length = 0;
    list->size = size;
    return list;
}


size_t DoubleCircularLinkedList_length(DoubleCircularLinkedList* list) {
    return (list != NULL) ? list->length : -1;
}


ssize_t DoubleCircularLinkedList_size(DoubleCircularLinkedList* list) {
    return (list != NULL) ? list->size : -1;
}


int _DoubleCircularLinkedList_is_exceed_size(DoubleCircularLinkedList* list) {
    return (list != NULL) ? (list->size != -1) && (list->length + 1 > list->size) : -1;
}


int DoubleCircularLinkedList_is_empty(DoubleCircularLinkedList* list) {
    return (list == NULL) ?
        (list->head->next = list->head) || (list->head->prev == list->head) : -1;
}


int
DoubleCircularLinkedList_push_front(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType data) {

    if (list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (_DoubleCircularLinkedList_is_exceed_size(list)) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    DoubleCircularLinkedListNode* node = 
        (DoubleCircularLinkedListNode*) malloc (sizeof(DoubleCircularLinkedListNode));

    if (node == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_NODE_INIT_ERROR);
        return -1;
    }

    node->data = data;

    node->prev = list->head;
    node->next = list->head->next;
    list->head->next->prev = node;
    list->head->next = node;

    list->length++;

    return 0;
}


int DoubleCircularLinkedList_push_back(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType data) {
    
    if (list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (_DoubleCircularLinkedList_is_exceed_size(list)) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    DoubleCircularLinkedListNode* node = 
        (DoubleCircularLinkedListNode*) malloc (sizeof(DoubleCircularLinkedListNode));

    if (node == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_NODE_INIT_ERROR);
        return -1;
    }

    node->data = data;

    node->next = list->head;
    node->prev = list->head->prev;
    list->head->prev->next = node;
    list->head->prev = node;

    list->length++;
    return 0;
}


int
DoubleCircularLinkedList_insert(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType data, size_t pos) {

    if (list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (pos == 0 || pos > list->length + 1 ||
         _DoubleCircularLinkedList_is_exceed_size(list)) {

        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    if (list->length == 0) {
        return DoubleCircularLinkedList_push_back(list, data);
    }

    DoubleCircularLinkedListNode* prev = list->head;
    for (size_t i = 1; i < pos; i++) {
        prev = prev->next;
    }

    DoubleCircularLinkedListNode* node = 
        (DoubleCircularLinkedListNode*)malloc(sizeof(DoubleCircularLinkedListNode));
    if (node == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_NODE_INIT_ERROR);
        return -1;
    }
    node->data = data;

    node->next = prev->next;
    node->prev = prev;
    prev->next->prev = node;
    prev->next = node;
    list->length++;
    return 0;
}


int
DoubleCircularLinkedList_pop_front(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data) {

    if (list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (list->length == 0) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    DoubleCircularLinkedListNode* node = list->head->next;
    *data = node->data;
    node->next->prev = list->head;
    list->head->next = node->next;
    free(node);
    list->length--;
    return 0;
}


int
DoubleCircularLinkedList_pop_back(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data) {

    if (list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (list->length == 0) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    DoubleCircularLinkedListNode* node = list->head->prev;
    *data = node->data;
    node->prev->next = list->head;
    list->head->prev = node->prev;
    free(node);
    list->length--;
    return 0;
}


int 
DoubleCircularLinkedList_remove(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data,
        size_t* pos, int mode) {

    if (list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (list->length == 0) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    if (data == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_REMOVE_EXCEPTION);
        return -1;
    }

    if (mode == DOUBLE_CIRCULAR_LINKED_LIST_SEARCH_BY_POS 
            && pos != NULL && *pos != 0 && *pos < list->length) {

        DoubleCircularLinkedListNode* current = list->head->next;
        size_t count = 1;

        while ((current != list->head) && (count < *pos)) {
            current = current->next;
            count++;
        }
        *data = current->data;
        current->prev->next = current->next;
        current->next->prev = current->prev;
        list->length--;
        free(current);
    } 
    else if (mode == DOUBLE_CIRCULAR_LINKED_LIST_SEARCH_BY_VALUE) {
        DoubleCircularLinkedListNode* current = list->head->next;

        while ((current != list->head)) {
            if (current->data == (*data)) {
                DoubleCircularLinkedListNode* t = current;
                current->prev->next = current->next;
                current->next->prev = current->prev;
                list->length--;
                current = current->next;
                free(t);
                break;
            } else {
                current = current->next;
            }
        }
    }
    else {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_REMOVE_EXCEPTION);
        return -1;
    }

    return 0;
}


int
DoubleCircularLinkedList_front(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data) {

    if (list == NULL || list->length == 0) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_CHECK_ERROR);
        return -1;
    }
    *data = list->head->next->data;
    return 0;
}


int 
DoubleCircularLinkedList_back(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data) {

    if (list == NULL || list->length == 0) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_CHECK_ERROR);
        return -1;
    }
    
    *data = list->head->prev->data;
    return 0;
}


int 
DoubleCircularLinkedList_search(
    DoubleCircularLinkedList* list, DoubleCircularLinkedListEleType* data,
    size_t* pos, int mode) {

    if (list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (data == NULL || pos == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_SEARCH_EXCEPTION);
        return -1;
    }

    if (
        mode == DOUBLE_CIRCULAR_LINKED_LIST_SEARCH_BY_POS &&
            (*pos > list->length || *pos == 0)
    ) {

        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_SEARCH_EXCEPTION);
        return -1;
    }

    if (mode == DOUBLE_CIRCULAR_LINKED_LIST_SEARCH_BY_POS) {
        DoubleCircularLinkedListNode* current = list->head->next;
        size_t count = 1;

        while ((current != list->head) && (count < *pos)) {
            current = current->next;
            count++;
        }
        *data = current->data;
    }
    else if (mode == DOUBLE_CIRCULAR_LINKED_LIST_SEARCH_BY_VALUE) {
        DoubleCircularLinkedListNode* current = list->head->next;
        size_t count = 1;
        int search_state = 0;

        while (current != list->head && count <= list->length) {
            if (current->data == *data) {
                search_state = 1;
                *pos = count;
                break;
            }
            current = current->next;
            count++;
        }

        if (search_state == 0) {
            fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_SEARCH_EXCEPTION);
            return -1;
        }
    }
    else {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_SEARCH_MODE_ERROR);
        return -1;
    }

    return 0;
}


int DoubleCircularLinkedList_display(DoubleCircularLinkedList* list){
    if (list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    DoubleCircularLinkedListNode* current = list->head->next;
    printf("DoubleCircularLinkedList: {  ");
    while (current != list->head) {
        printf("%d  ", current->data);
        current = current->next;
    }
    printf("}  length: %zu  size: %zd\n", list->length, list->size);
    return 0;
}


int DoubleCircularLinkedList_clean(DoubleCircularLinkedList** list){
    if (list == NULL || *list == NULL) {
        fprintf(stderr, DOUBLE_CIRCULAR_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    DoubleCircularLinkedListNode* current = (*list)->head->next;
    while (current != (*list)->head) {
        DoubleCircularLinkedListNode* old = current;
        current = current->next;
        free(old);
    }
    free((*list)->head);
    free(*list);
    (*list) = NULL;
    return 0;
}
