#include <stdio.h>
#include <stdlib.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define INIT_DATA 0


typedef int EleType;


typedef struct LinkedListNode {
    EleType data;
    struct LinkedListNode* next; 
} LinkedListNode;


typedef struct LinkdeList {
    LinkedListNode* head;

    size_t length;

    ssize_t size;
} LinkdeList;


LinkdeList* linkedlist_create(ssize_t size) {
    LinkdeList* list = (LinkdeList*)malloc(sizeof(LinkdeList));
    if (list == NULL) {
        fprintf(stderr, "Failed to allocate memory for the LinkedList\n");
        return NULL;
    }
    list->length = 0;
    list->size = size;

    return list;
}


size_t linkedlist_length(LinkdeList* list) {
    return list->length;
}


ssize_t linkedlist_size(LinkdeList* list) {
    return list->size;
}


int _linkedlist_is_exceed(LinkdeList* list) {
    return ((list->size != -1)
        && (list->length + 1 > list->size)) ? 1 : 0;
}


int linkedlist_display(LinkdeList* list) {
    if (list == NULL) {
        fprintf(
            stderr, 
            "Parameter is incorrect. Please check whether the `LinkedList` type parameter is passed\n"
        );

        return -1;
    }
    LinkedListNode* current = list->head;
    while (current != NULL) {
        printf("%d  ", current->data);
        current = current->next;
    }
    puts("");
    printf("length: %zu, max: %zd\n\n", list->length, list->size);
    return 0;
}


int linkedlist_push_front(LinkdeList* list, EleType data) {
    if (_linkedlist_is_exceed(list) || list == NULL) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }

    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory for the LinkedListNode\n");
        return -1;
    }

    node->data = data;

    if (list->length == 0) {
        node->next = NULL;
        list->head = node;
    }

    node->next = list->head;
    list->head = node;
    list->length++;

    return 0;
}


int linkedlist_push_back(LinkdeList* list, EleType data) {
    if (_linkedlist_is_exceed(list) || list == NULL) {
        fprintf(stderr, "`LinkedList` Exceed capacity limit\n");
        return -1;
    }

    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory for the `LinkedListNode`\n");
        return -1;
    }
    node->data = data;
    LinkedListNode* current = list->head;

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


int linkedlist_insert(LinkdeList* list, EleType data, size_t pos) {
    if (_linkedlist_is_exceed(list) || list == NULL) {
        fprintf(stderr, "`LinkedList` Exceed capacity limit\n");
        return -1;
    }

    if (pos > list->length) {
        fprintf(stderr, "`LinkedList` Index overshoot\n");
        return -1;
    } else {
        LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        node->data = data;

        LinkedListNode* current = list->head;
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


int linkedlist_remove(LinkdeList* list, size_t pos) {
    if (list == NULL) {
        fprintf(
            stderr, 
            "Parameter is incorrect. Please check whether the `LinkedList` type parameter is passed\n"
        );

        return -1;
    }

    if (pos > list->length) {
        fprintf(stderr, "`LinkedList` Index overshoot\n");
        return -1;
    } else {

        LinkedListNode* current = list->head;
        size_t count = 1;

        while ((current->next != NULL) && (count < pos - 1)) {
            current = current->next;
            count++;
        }

        LinkedListNode* old = current->next;
        current->next = current->next->next;
        free(old);
        list->length--;
        return 0;
    }
}


int linkedlist_search(LinkdeList* list, EleType** data, size_t** pos) {
    if (list == NULL) {
        fprintf(
            stderr, 
            "Parameter is incorrect. Please check whether the `LinkedList` type parameter is passed\n"
        );
        return -1;
    }

    if (*pos != NULL && **pos > list->length) {
        fprintf(stderr, "`LinkedList` Index overshoot\n");
        return -1;
    }
    else if (*pos != NULL && *data == NULL) {

        LinkedListNode* current = list->head;
        size_t count = 1;

        while ((current != NULL) && (count < **pos)) {
            current = current->next;
            count++;
        }
        printf("%zu\n", count);
        *data = (EleType*)malloc(sizeof(EleType));
        **data = current->data;
    }
    else if (*pos == NULL && *data != NULL) {
        LinkedListNode* current = list->head;
        size_t count = 1;
        int search_state = 0;

        while (current != NULL) {
            if (current->data == **data) {
                search_state = 1;
                *pos = (size_t*)malloc(sizeof(size_t));
                **pos = count;
                break;
            }
            current = current->next;
            count++;
        }

        if (search_state == 0) {
            return -1;
        }
    } 
    else {
        fprintf(stderr, "`LinkedList` Search mode error\n");
        return -1;
    }

    return 0;
}


int linkedlist_pop_front(LinkdeList* list, EleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "`LinkedList` Exceed capacity limit\n");
        return -1;
    }
    LinkedListNode* node = list->head;
    *data = list->head->data;
    list->head = list->head->next;
    list->length--;
    free(node);
    return 0;
}


int linkedlist_pop_back(LinkdeList* list, EleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }

    LinkedListNode* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    *data = current->next->data;

    list->length--;

    free(current->next);

    current->next = NULL;

    return 0;
}


int linkedlist_front(LinkdeList* list, EleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }
    *data = list->head->data;
    return 0;
}


int linkedlist_back(LinkdeList* list, EleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "`LinkedList` Exceed capacity limit\n");
        return -1;
    }
    LinkedListNode* current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }
    *data = current->data;
    return 0;
}


int linkedlist_clean(LinkdeList* list) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "`LinkedList` Exceed capacity limit\n");
        return -1;
    }

    LinkedListNode* current = list->head;
    while (current->next != NULL) {
        LinkedListNode* old = current;
        current = current->next;
        free(old);
    }
    free(list);
    return 0;
}


int main(int argc, char const *argv[]) {
    
    LinkdeList* list = linkedlist_create(-1);

    puts("  push back: ");
    linkedlist_push_back(list, 2333);
    linkedlist_push_back(list, 23333);
    linkedlist_push_back(list, 233333);
    linkedlist_display(list);


    puts("  push front: ");
    linkedlist_push_front(list, 23);
    linkedlist_display(list);


    puts("  insert 2: ");
    linkedlist_insert(list, 233, 2);
    linkedlist_display(list);


    puts("  remove 5: ");
    linkedlist_remove(list, 5);
    linkedlist_display(list);


    EleType ele;


    puts("  pop front ");
    linkedlist_pop_front(list, &ele);
    linkedlist_display(list);
    printf("popped element is: %d\n", ele);


    puts("  pop back ");
    linkedlist_pop_back(list, &ele);
    linkedlist_display(list);
    printf("popped element is:%d\n", ele);


    puts("  lookup:");
    printf("fornt element is: %d\n", ele);
    linkedlist_front(list, &ele);
    linkedlist_display(list);

    printf("back element is: %d\n", ele);
    linkedlist_back(list, &ele);
    linkedlist_display(list);

    puts("  search:");
    size_t seq = 2;
    size_t* pos = &seq;
    EleType* res = NULL;
    if (linkedlist_search(list, &res, &pos) == 0) {
        printf("the 2 elemnet is: %d\n", *res);
        free(res);
    }
    

    size_t* target = NULL;
    ele = 2333;
    res = &ele;
    if (linkedlist_search(list, &res, &target) == 0) {
        printf("the 2333 elemnet pos is: %zu\n", *target);
        free(target); // 确保释放内存
    } else {
        printf("Element 23333 not found.\n");
    }

    linkedlist_clean(list);

    return 0;
}

