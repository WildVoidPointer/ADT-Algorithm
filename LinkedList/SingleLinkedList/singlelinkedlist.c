#include "singlelinkedlist.h"

int _singlelinkedlist_is_exceed(SingleLinkedList* list) {
    return ((list->size != -1)
        && (list->length + 1 > list->size)) ? 1 : 0;
}

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

size_t singlelinkedlist_length(SingleLinkedList* list) {
    return list->length;
}

ssize_t singlelinkedlist_size(SingleLinkedList* list) {
    return list->size;
}

int singlelinkedlist_push_front(SingleLinkedList* list, SingleLinkedListEleType data) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (_singlelinkedlist_is_exceed(list)) {
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

    if (_singlelinkedlist_is_exceed(list)) {
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

int singlelinkedlist_insert(SingleLinkedList* list, SingleLinkedListEleType data, size_t pos) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (_singlelinkedlist_is_exceed(list)) {
        fprintf(stderr, SINGLELINKEDLIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    if (pos > list->length || pos <= 0) {
        fprintf(stderr, SINGLELINKEDLIST_INSERT_EXCEPTION);
        return -1;
    } else {
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
        return 0;
    }
}

int singlelinkedlist_remove(SingleLinkedList* list, size_t pos) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (pos > list->length || pos <= 0) {
        fprintf(stderr, SINGLELINKEDLIST_INSERT_EXCEPTION);
        return -1;
    } else {

        SingleLinkedListNode* current = list->head;
        size_t count = 1;

        while ((current->next != NULL) && (count < pos - 1)) {
            current = current->next;
            count++;
        }

        SingleLinkedListNode* old = current->next;
        current->next = current->next->next;
        free(old);
        list->length--;
        return 0;
    }
}

int singlelinkedlist_search(SingleLinkedList* list, SingleLinkedListEleType* data, size_t* pos, int flag) {
    if (list == NULL) {
        fprintf(stderr, SINGLELINKEDLIST_ACCESS_ERROR);
        return -1;
    }

    if (flag == 0 && (*pos > list->length || *pos <= 0)) {
        fprintf(stderr, SINGLELINKEDLIST_SEARCH_EXCEPTION);
        return -1;
    }

    if (flag == 0) {
        SingleLinkedListNode* current = list->head;
        size_t count = 1;

        while ((current != NULL) && (count < *pos)) {
            current = current->next;
            count++;
        }
        *data = current->data;
    }
    else if (flag == -1) {
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
