#include "singly_linked_list.h"


SLinkedList* SLinkedList_create(ssize_t size) {

    SLinkedList* list = (SLinkedList*)malloc(sizeof(SLinkedList));
    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_INIT_ERROR);
        return NULL;
    }
    list->length = 0;
    list->size = size;
    return list;
}


int _SLinkedList_is_exceed_size(SLinkedList* list) {
    return (list != NULL) ? 
        (list->size != -1) && (list->length + 1 > list->size) : -1;
}


size_t SLinkedList_length(SLinkedList* list) {
    return (list != NULL) ? list->length : -1;
}


ssize_t SLinkedList_size(SLinkedList* list) {
    return (list != NULL) ? list->size : -1;
}


int SLinkedList_is_empty(SLinkedList* list) {
    return (list == NULL) ? list->length == 0 : -1;
}


int SLinkedList_push_front(SLinkedList* list, SLinkedListDataType data) {
    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (_SLinkedList_is_exceed_size(list)) {
        fprintf(stderr, S_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    SLinkedListNode* node = (SLinkedListNode*)malloc(sizeof(SLinkedListNode));
    if (node == NULL) {
        fprintf(stderr, S_LINKED_LIST_NODE_INIT_ERROR);
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


int 
SLinkedList_push_back(SLinkedList* list, SLinkedListDataType data) {
    
    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (_SLinkedList_is_exceed_size(list)) {
        fprintf(stderr, S_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    SLinkedListNode* node = 
        (SLinkedListNode*)malloc(sizeof(SLinkedListNode));

    if (node == NULL) {
        fprintf(stderr, S_LINKED_LIST_NODE_INIT_ERROR);
        return -1;
    }
    node->data = data;
    SLinkedListNode* current = list->head;

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
SLinkedList_insert(
    SLinkedList* list, SLinkedListDataType data, size_t pos) {

    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (_SLinkedList_is_exceed_size(list)) {
        fprintf(stderr, S_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    if (pos > list->length || pos == 0 || SLinkedList_is_empty(list)) {
        fprintf(stderr, S_LINKED_LIST_INSERT_EXCEPTION);
        return -1;
    } 

    if (pos == 1) {

        SLinkedListNode* node = 
            (SLinkedListNode*)malloc(sizeof(SLinkedListNode));

        if (node == NULL) {
            fprintf(stderr, S_LINKED_LIST_NODE_INIT_ERROR);
            return -1;
        }

        node->data = data;
        node->next = list->head;
        list->head = node;
        list->length++;

    } else if (pos == list->length + 1){
        SLinkedListNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }

        SLinkedListNode* node = 
            (SLinkedListNode*)malloc(sizeof(SLinkedListNode));

        if (node == NULL) {
            fprintf(stderr, S_LINKED_LIST_NODE_INIT_ERROR);
            return -1;
        }
        current->next = node;
        node->data = data;
        list->length++;

    } else if (pos <= list->length) {

        SLinkedListNode* node = 
            (SLinkedListNode*)malloc(sizeof(SLinkedListNode));

        if (node == NULL) {
            fprintf(stderr, S_LINKED_LIST_NODE_INIT_ERROR);
            return -1;
        }

        node->data = data;

        SLinkedListNode* current = list->head;
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


int SLinkedList_remove(
    SLinkedList* list, SLinkedListDataType* data, 
    size_t pos, SLinkedListSearchModeEnum mode) {

    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }
    if (data == NULL) {
        fprintf(stderr, S_LINKED_LIST_REMOVE_EXCEPTION);
        return -1;
    }

    if (mode == S_LINKED_LIST_SEARCH_BY_POS && pos != 0 && pos < list->length) {

        SLinkedListNode* current = list->head;
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
    
            SLinkedListNode* target = current->next;
            current->next = target->next;
            *data = target->data;
            free(target);
            list->length--;
        }   
    }
    else if (mode == S_LINKED_LIST_SEARCH_BY_VALUE) {
        SLinkedListNode* temp = NULL;
        if (list->head->data == *data) {
            temp = list->head;
            list->head = list->head->next;
            list->length--;
            free(temp);
        } else {
            SLinkedListNode* current = list->head;
        
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
        fprintf(stderr, S_LINKED_LIST_REMOVE_EXCEPTION);
        return -1;
    }

    return 0;
}


int
SLinkedList_search(
    SLinkedList* list, SLinkedListDataType* data, 
    size_t* pos, SLinkedListSearchModeEnum mode) {
        
    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (data == NULL) {
        fprintf(stderr, S_LINKED_LIST_SEARCH_EXCEPTION);
        return -1;
    }

    if (mode == S_LINKED_LIST_SEARCH_BY_POS && (*pos < list->length || *pos != 0)) {
        SLinkedListNode* current = list->head;
        size_t count = 1;

        while ((current != NULL) && (count < *pos)) {
            current = current->next;
            count++;
        }
        *data = current->data;
    }
    else if (mode == S_LINKED_LIST_SEARCH_BY_VALUE) {
        SLinkedListNode* current = list->head;
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
            fprintf(stderr, S_LINKED_LIST_SEARCH_EXCEPTION);
            return -1;
        }
    }

    else {
        fprintf(stderr, S_LINKED_LIST_SEARCH_MODE_ERROR);
        return -1;
    }

    return 0;
}


int SLinkedList_pop_front(SLinkedList* list, SLinkedListDataType* data) {
    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (list->length == 0) {
        fprintf(stderr, S_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }
    SLinkedListNode* node = list->head;
    *data = list->head->data;
    list->head = list->head->next;
    list->length--;
    free(node);
    return 0;
}


int SLinkedList_pop_back(SLinkedList* list, SLinkedListDataType* data) {
    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (list->length == 0) {
        fprintf(stderr, S_LINKED_LIST_OVERFLOW_EXCEPTION);
        return -1;
    }

    SLinkedListNode* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    *data = current->next->data;

    list->length--;

    free(current->next);

    current->next = NULL;

    return 0;
}


int SLinkedList_front(SLinkedList* list, SLinkedListDataType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, S_LINKED_LIST_CHECK_ERROR);
        return -1;
    }
    *data = list->head->data;
    return 0;
}


int SLinkedList_back(SLinkedList* list, SLinkedListDataType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, S_LINKED_LIST_CHECK_ERROR);
        return -1;
    }
    
    SLinkedListNode* current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }
    *data = current->data;
    return 0;
}


int SLinkedList_reverse(SLinkedList* list) {
    
    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    if (list->head == NULL || list->head->next == NULL) {
        return 0;
    }

    SLinkedListNode* prev = NULL;
    SLinkedListNode* current = list->head;
    SLinkedListNode* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    list->head = prev;

    return 0;
}


int
SLinkedList_recursion_reverse(SLinkedList* list) {
    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }
    
    list->head = _SLinkedList_recursion_reverse_node(list->head);
    return 0;
}


SLinkedListNode* 
_SLinkedList_recursion_reverse_node(SLinkedListNode* node) {
    if (node ==  NULL || node->next == NULL) {
        return node;
    }

    SLinkedListNode* tmp = _SLinkedList_recursion_reverse_node(node->next);

    node->next->next = node;
    node->next =  NULL;

    return tmp;
}


int SLinkedList_display(SLinkedList* list) {
    if (list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    SLinkedListNode* current = list->head;
    printf("SLinkedList: {  ");
    while (current != NULL) {
        printf("%d  ", current->data);
        current = current->next;
    }
    printf("}  length: %zu  size: %zd\n", list->length, list->size);
    return 0;
}


int SLinkedList_destroy(SLinkedList** list) {
    if (list == NULL || *list == NULL) {
        fprintf(stderr, S_LINKED_LIST_ACCESS_ERROR);
        return -1;
    }

    SLinkedListNode* current = (*list)->head;
    while (current != NULL) {
        SLinkedListNode* old = current;
        current = current->next;
        free(old);
    }
    free(*list);
    (*list) = NULL;
    return 0;
}
