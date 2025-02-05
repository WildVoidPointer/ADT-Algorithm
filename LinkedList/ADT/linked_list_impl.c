#include <stdio.h>
#include <stdlib.h>

#define INIT_DATA 0

typedef int EleType;


typedef struct LinkedNode {
    EleType data;
    struct LinkedNode* next; 
} LinkedNode;


typedef struct LinkdeList {
    LinkedNode* head;

    size_t length;

    ssize_t size; 
} LinkdeList;


LinkdeList* create(ssize_t size) {
    LinkdeList* list = (LinkdeList*)malloc(sizeof(LinkdeList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    list->length = 0;
    list->size = size;

    return list;
}


size_t length(LinkdeList* list) {
    return list->length;
}


ssize_t size(LinkdeList* list) {
    return list->size;
}


int _is_exceed(LinkdeList* list) {
    return ((list->size != -1)
        && (list->length + 1 > list->size)) ? 1 : 0;
}


int display(LinkdeList* list) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }
    LinkedNode* current = list->head;
    while (current != NULL) {
        printf("%d  ", current->data);
        current = current->next;
    }
    puts("");
    printf("length: %zu, max: %zd\n", list->length, list->size);
    return 0;
}


int push_front(LinkdeList* list, EleType data) {
    if (_is_exceed(list) || list == NULL) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }

    LinkedNode* node = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
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


int push_back(LinkdeList* list, EleType data) {
    if (_is_exceed(list) || list == NULL) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }

    LinkedNode* node = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    node->data = data;
    LinkedNode* current = list->head;

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


int insert_item(LinkdeList* list, EleType data, size_t pos) {
    if (_is_exceed(list) || list == NULL) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }

    if (pos > list->length) {
        fprintf(stderr, "Index overshoot\n");
        return -1;
    } else {
        LinkedNode* node = (LinkedNode*)malloc(sizeof(LinkedNode));
        node->data = data;

        LinkedNode* current = list->head;
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


int remove_item(LinkdeList* list, size_t pos) {
    if (pos > list->length || list == NULL) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }

    if (pos > list->length) {
        fprintf(stderr, "Index overshoot\n");
        return -1;
    } else {

        LinkedNode* current = list->head;
        size_t count = 1;

        while ((current->next != NULL) && (count < pos - 1)) {
            current = current->next;
            count++;
        }

        LinkedNode* old = current->next;
        current->next = current->next->next;
        free(old);
        list->length--;
        return 0;
    }
}


int get_item(LinkdeList* list, EleType* data, size_t pos) {
    if (pos > list->length || list == NULL) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }

    if (pos > list->length) {
        fprintf(stderr, "Index overshoot\n");
        return -1;
    } else {

        LinkedNode* current = list->head;
        size_t count = 1;

        while ((current->next != NULL) && (count < pos - 1)) {
            current = current->next;
            count++;
        }

        LinkedNode* old = current->next;
        current->next = current->next->next;
        *data = old->data;
        free(old);
        list->length--;
        return 0;
    }
}


int pop_front(LinkdeList* list, EleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }
    LinkedNode* node = list->head;
    *data = list->head->data;
    list->head = list->head->next;
    list->length--;
    free(node);
    return 0;
}


int pop_back(LinkdeList* list, EleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }

    LinkedNode* current = list->head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    *data = current->next->data;

    list->length--;

    free(current->next);

    current->next = NULL;

    return 0;
}


int front(LinkdeList* list, EleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }
    *data = list->head->data;
    return 0;
}


int back(LinkdeList* list, EleType* data) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }
    LinkedNode* current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }
    *data = current->data;
    return 0;
}


int destroy(LinkdeList* list) {
    if (list == NULL || list->length == 0) {
        fprintf(stderr, "Exceed capacity limit\n");
        return -1;
    }

    LinkedNode* current = list->head;
    while (current->next != NULL) {
        LinkedNode* old = current;
        current = current->next;
        free(old);
    }
    free(list);
    return 0;
}


int main(int argc, char const *argv[]) {
    
    LinkdeList* list = create(-1);

    push_back(list, 233);
    push_back(list, 2333);
    push_back(list, 23333);
    display(list);


    push_front(list, 23);
    display(list);


    insert_item(list, 73, 2);
    display(list);

    remove_item(list, 2);
    display(list);

    EleType ele;
    pop_front(list, &ele);
    display(list);
    printf("%d\n", ele);

    pop_back(list, &ele);
    printf("%d\n", ele);
    display(list);

    front(list, &ele);
    printf("%d\n", ele);
    display(list);

    get_item(list, &ele, 3);
    printf("%d\n", ele);

    back(list, &ele);
    printf("%d\n", ele);
    display(list);

    destroy(list);

    return 0;
}

