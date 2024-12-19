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


typedef bool (*PushBackLinkTable)(struct LinkedList*, EleType);

typedef bool (*PushFrontLinkTable)(struct LinkedList*, EleType);

typedef EleType (*GetElementLinkTable)(struct LinkedList*, int);

typedef bool (*RemoveElementLinkTable)(struct LinkedList*, EleType);

typedef int (*GetLenLinkTable)(struct LinkedList*);

typedef EleType (*GetElementByPos)(struct LinkedList*, int);

typedef bool (*InsertElemnetLinkTable)(struct LinkedList*, int, EleType);

typedef void (*DestroyElementLinkTable)(struct LinkedList*);

typedef void (*DisplayLinkTable)(struct LinkedList*);

typedef struct LinkedList {
    LinkedNode *head;

    PushBackLinkTable push_back;
    PushFrontLinkTable push_front;
    GetElementLinkTable get;
    RemoveElementLinkTable remove;
    GetLenLinkTable len;
    GetElementByPos get_ele_by_pos;
    InsertElemnetLinkTable insert;
    DisplayLinkTable display;
    DestroyElementLinkTable destroy;
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


int len(LinkedList *table) {
    int _count = 0;
    LinkedNode *current = table->head;
    while (current != NULL) {
        _count++;
        current = current->next;
    }
    return _count;
}


bool insert(LinkedList *table, int pos, EleType ele) {
    if (pos < 0 || pos > table->len(table)) {
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

    int _count = 0;
    LinkedNode *current = table->head;
    while (current != NULL && _count < pos - 1) {
        _count++;
        current = current->next;
    }

    _new->next = current->next;
    current->next = _new;
    return true;
}


EleType get(LinkedList *table, int pos) {
    if ((pos > table->len(table)) || 
        pos < 0 || table->head == NULL) {
            fprintf(stderr, "Invailid Paraments\n");
            return 0;
        }

    int _count = 0;
    LinkedNode *current = table->head;
    while (current != NULL && _count < pos) {
        _count++;
        current = current->next;
    }
    return current->data;  
}


EleType get_ele_by_pos(LinkedList *table, int pos) {
    LinkedNode *current = table->head;
    int count = 0;
    while (current != NULL) {
        if (count == pos) {
            return current->data;
        }
        count++;
        current = current->next;
    }
    return -1;
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
    table.len = len;
    table.get = get;
    table.get_ele_by_pos = get_ele_by_pos;
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
    printf("length: %d\n", table.len(&table));
    printf("caputrue element: %d\n", table.get(&table, 2));


    table.push_front(&table, 233);
    table.display(&table);
    printf("length: %d\n", table.len(&table));

    table.insert(&table, 3, 233);
    table.display(&table);
    printf("length: %d\n", table.len(&table));

    printf("The specific element: %d\n", table.get_ele_by_pos(&table, 4));

    table.destroy(&table);
    table.display(&table);
    printf("length: %d\n", table.len(&table));

    return 0;
}
