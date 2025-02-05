#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int EleType;

struct LinkedList;


typedef struct LinkedNode {
    EleType data;
    struct LinkedNode *next;
} LinkedNode;


LinkedNode* create_node(EleType ele) {
    LinkedNode *new_node = (LinkedNode *)malloc(sizeof(LinkedNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    new_node->data = ele;
    new_node->next = NULL;
    return new_node;
}


typedef bool (*PushBackToLinkedList)(struct LinkedList*, EleType);

typedef bool (*PushFrontToLinkedList)(struct LinkedList*, EleType);

typedef EleType (*GetEleFromLinkedList)(struct LinkedList*, int);

typedef bool (*RemoveEleFromLinkedList)(struct LinkedList*, EleType);

typedef int (*GetLenOfLinkedList)(struct LinkedList*);

typedef bool (*InsertEleToLinkedList)(struct LinkedList*, int, EleType);

typedef void (*DestroyLinkedList)(struct LinkedList*);

typedef void (*DisplayLinkedList)(struct LinkedList*);


typedef struct LinkedList {
    LinkedNode *head;

    PushBackToLinkedList push_back;
    PushFrontToLinkedList push_front;
    GetEleFromLinkedList get;
    RemoveEleFromLinkedList remove;
    GetLenOfLinkedList length;
    InsertEleToLinkedList insert;
    DisplayLinkedList display;
    DestroyLinkedList destroy;
} LinkedList;


bool push_back(LinkedList *table, EleType ele) {
    LinkedNode *new_node = create_node(ele);
    if (new_node == NULL) {
        return false;
    }
    
    if (table->head == NULL) {
        table->head = new_node;
    } else {
        LinkedNode *current = table->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    return true;
}


bool push_front(LinkedList *table, EleType ele) {
    LinkedNode *_new = create_node(ele);
    if (_new == NULL) {
        return false;
    }

    _new->next = table->head;
    table->head = _new;
    return true;
}


int length(LinkedList *table) {
    int _count = 0;
    LinkedNode *current = table->head;
    while (current != NULL) {
        _count++;
        current = current->next;
    }
    return _count;
}


bool insert(LinkedList *table, int pos, EleType ele) {
    if (pos < 0 || pos > table->length(table)) {
        fprintf(stderr, "Invalid Parameters\n");
        return false;
    }

    LinkedNode *_new = create_node(ele);
    if (_new == NULL) {
        return false;
    }

    if (pos == 0) {
        _new->next = table->head;
        table->head = _new;
        return true;
    }

    int count = 0;
    LinkedNode *current = table->head;
    while (current != NULL && count < pos - 1) {
        count++;
        current = current->next;
    }

    _new->next = current->next;
    current->next = _new;
    return true;
}


EleType get(LinkedList *table, int pos) {
    if ((pos > table->length(table)) || 
        pos < 0 || table->head == NULL) {
            fprintf(stderr, "Invailid Paraments\n");
            return 0;
        }

    int count = 0;
    LinkedNode *current = table->head;
    while (current != NULL && count < pos) {
        count++;
        current = current->next;
    }
    return current->data;  
}


void display(LinkedList *table) {
    LinkedNode *current = table->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    puts("NULL");
}


void destroy(LinkedList *table) {
    LinkedNode *current = table->head;
    while (current != NULL) {
        LinkedNode *_tmp = current->next;
        free(current);
        current = _tmp;
    }
    table->head = NULL;
}


LinkedList create_table() {
    LinkedList table;
    table.head = NULL;
    table.push_back = push_back;
    table.push_front = push_front;
    table.length = length;
    table.get = get;
    table.insert = insert;
    table.display = display;
    table.destroy = destroy;
    return table;
}


int main() {
    LinkedList table = create_table();

    table.push_back(&table, 10);
    table.push_back(&table, 20);
    table.push_back(&table, 30);

    table.display(&table);
    printf("length: %d\n", table.length(&table));
    printf("caputrue element: %d\n", table.get(&table, 2));


    table.push_front(&table, 233);
    table.display(&table);
    printf("length: %d\n", table.length(&table));

    table.insert(&table, 3, 233);
    table.display(&table);
    printf("length: %d\n", table.length(&table));

    table.destroy(&table);
    table.display(&table);
    printf("length: %d\n", table.length(&table));

    return 0;
}
