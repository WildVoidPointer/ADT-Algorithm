#include "singlelinkedlist.h"


SingleLinkedList* singlelinkedlist_create(ssize_t size) {
    SingleLinkedList* list = (SingleLinkedList*)malloc(sizeof(SingleLinkedList));
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_INIT_ERROR);
        return NULL;
    }
    list->length = 0;
    list->size = size;
    return list;
}


int _singlelinkedlist_is_exceed_size(SingleLinkedList* list) {
    return (list != NULL) ? 
        (list->size != -1) && (list->length + 1 > list->size) : -1;
}


size_t singlelinkedlist_length(SingleLinkedList* list) {
    return (list != NULL) ? list->length : -1;
}


ssize_t singlelinkedlist_size(SingleLinkedList* list) {
    return (list != NULL) ? list->size : -1;
}


int singlelinkedlist_is_empty(SingleLinkedList* list) {
    return (list == NULL) ? list->length == 0 : -1;
}


int singlelinkedlist_push_front(SingleLinkedList* list, SingleLinkedListEleType data) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (_singlelinkedlist_is_exceed_size(list)) {
        fprintf(stderr, SINGLELINKEDLIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    SingleLinkedListNode* node = (SingleLinkedListNode*)malloc(sizeof(SingleLinkedListNode));
    if (node == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_NODE_INIT_ERROR);
        return -1;
    }

    node->data = data;

    if (list->length == 0) {
        node->next = NULL;
        list->head = node;
    } else {
        node->next = list->head;
        list->head = node;
    }

    list->length++;
    return 0;
}


int singlelinkedlist_push_back(SingleLinkedList* list, SingleLinkedListEleType data) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (_singlelinkedlist_is_exceed_size(list)) {
        fprintf(stderr, SINGLELINKEDLIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    SingleLinkedListNode* node = (SingleLinkedListNode*)malloc(sizeof(SingleLinkedListNode));
    if (node == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_NODE_INIT_ERROR);
        return -1;
    }
    node->data = data;
    SingleLinkedListNode* current = list->head;

    if (list->length == 0) {
        node->next = NULL;
        list->head = node;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = node;
    }

    list->length++;
    return 0;
}


int
singlelinkedlist_insert(SingleLinkedList* list, SingleLinkedListEleType data, size_t pos) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (_singlelinkedlist_is_exceed_size(list)) {
        fprintf(stderr, SINGLELINKEDLIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    if (pos > list->length || pos == 0 || singlelinkedlist_is_empty(list)) {
        fprintf(stderr, SINGLELINKEDLIST_INSERT_EXCEPTION);
        return -1;
    } 

    if (pos == 1) {
        SingleLinkedListNode* node = (SingleLinkedListNode*)malloc(sizeof(SingleLinkedListNode));
        if (node == NULL) {
            fprintf(stderr, SINGLELINKEDLIST_NODE_INIT_ERROR);
            return -1;
        }

        node->data = data;
        node->next = list->head;
        list->head = node;
        list->length++;

    } else if (pos == list->length + 1){
        SingleLinkedListNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }

        SingleLinkedListNode* node = (SingleLinkedListNode*)malloc(sizeof(SingleLinkedListNode));
        if (node == NULL) {
            fprintf(stderr, SINGLELINKEDLIST_NODE_INIT_ERROR);
            return -1;
        }
        current->next = node;
        node->data = data;
        list->length++;

    } else if (pos <= list->length) {
        SingleLinkedListNode* node = (SingleLinkedListNode*)malloc(sizeof(SingleLinkedListNode));
        if (node == NULL) {
            fprintf(stderr, SINGLELINKEDLIST_NODE_INIT_ERROR);
            return -1;
        }

        node->data = data;

        SingleLinkedListNode* current = list->head;
        size_t count = 1;

        while ((current->next != NULL) && (count < pos - 1)) {
            current = current->next;
            count++;
        }

        node->next = current->next;
        current->next = node;
        list->length++;
    }
    return 0;
}


int singlelinkedlist_remove(
    SingleLinkedList* list, SingleLinkedListEleType* data, size_t pos, int mode) {

    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }
    if (data == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_REMOVE_EXCEPTION);
        return -1;
    }

    if (mode == SINGLELINKEDLIST_SEARCH_BY_POS && pos != 0 && pos < list->length) {

        SingleLinkedListNode* current = list->head;
        size_t count = 1;

        if (pos == 1) {
            list->head = current->next;
            *data = current->data;
            free(current);
            list->length--;
        } else {
            while (current != NULL && count < pos - 1) {
                current = current->next;
                count++;
            }
    
            SingleLinkedListNode* target = current->next;
            current->next = target->next;
            *data = target->data;
            free(target);
            list->length--;
        }   
    }
    else if (mode == SINGLELINKEDLIST_SEARCH_BY_VALUE) {
        SingleLinkedListNode* temp = NULL;
        if (list->head->data == *data) {
            temp = list->head;
            list->head = list->head->next;
            list->length--;
            free(temp);
        } else {
            SingleLinkedListNode* current = list->head;
        
            while (current != NULL) {
                if (current->next != NULL && current->next->data == *data) {
                    temp = current->next;
                    current->next = temp->next;
                    list->length--;
                    free(temp);
                    break;
                } else {
                    current = current->next;
                }
            }
        }
    } else {
        fprintf(stderr, SINGLELINKEDLIST_REMOVE_EXCEPTION);
        return -1;
    }

    return 0;
}


int
singlelinkedlist_search(
    SingleLinkedList* list, SingleLinkedListEleType* data, size_t* pos, int mode) {
        
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (data == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_SEARCH_EXCEPTION);
        return -1;
    }

    if (mode == SINGLELINKEDLIST_SEARCH_BY_POS && (*pos < list->length || *pos != 0)) {
        SingleLinkedListNode* current = list->head;
        size_t count = 1;

        while ((current != NULL) && (count < *pos)) {
            current = current->next;
            count++;
        }
        *data = current->data;
    }
    else if (mode == SINGLELINKEDLIST_SEARCH_BY_VALUE) {
        SingleLinkedListNode* current = list->head;
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
            fprintf(stderr, SINGLELINKEDLIST_SEARCH_EXCEPTION);
            return -1;
        }
    }

    else {
        fprintf(stderr, SINGLELINKEDLIST_SEARCH_MODE_ERROR);
        return -1;
    }

    return 0;
}


int singlelinkedlist_pop_front(SingleLinkedList* list, SingleLinkedListEleType* data) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (list->length == 0) {
        fprintf(stderr, SINGLELINKEDLIST_OVERFLOW_EXCEPTION);
        return -1;
    }
    SingleLinkedListNode* node = list->head;
    *data = list->head->data;
    list->head = list->head->next;
    list->length--;
    free(node);
    return 0;
}


int singlelinkedlist_pop_back(SingleLinkedList* list, SingleLinkedListEleType* data) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (list->length == 0) {
        fprintf(stderr, SINGLELINKEDLIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    SingleLinkedListNode* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    *data = current->next->data;

    list->length--;

    free(current->next);

    current->next = NULL;

    return 0;
}


int singlelinkedlist_front(SingleLinkedList* list, SingleLinkedListEleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, SINGLELINKEDLIST_CHECK_ERROR);
        return -1;
    }
    *data = list->head->data;
    return 0;
}


int singlelinkedlist_back(SingleLinkedList* list, SingleLinkedListEleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, SINGLELINKEDLIST_CHECK_ERROR);
        return -1;
    }
    
    SingleLinkedListNode* current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }
    *data = current->data;
    return 0;
}


int singlelinkedlist_display(SingleLinkedList* list) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    SingleLinkedListNode* current = list->head;
    printf("SingleLinkedList: {  ");
    while (current != NULL) {
        printf("%d  ", current->data);
        current = current->next;
    }
    printf("}  length: %zu  size: %zd\n", list->length, list->size);
    return 0;
}


int singlelinkedlist_clean(SingleLinkedList** list) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    SingleLinkedListNode* current = (*list)->head;
    while (current != NULL) {
        SingleLinkedListNode* old = current;
        current = current->next;
        free(old);
    }
    free(*list);
    (*list) = NULL;
    return 0;
}
