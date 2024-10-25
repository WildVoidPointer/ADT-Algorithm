#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int EleType;
struct LinkTable;

typedef struct LinkNode {
    EleType data;
    struct LinkNode *next;
} LinkNode;


LinkNode* create_node(EleType ele) {
    LinkNode *new_node = (LinkNode *)malloc(sizeof(LinkNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    new_node->data = ele;
    new_node->next = NULL;
    return new_node;
}


typedef bool (*PushBackLinkTable)(struct LinkTable*, EleType);

typedef bool (*PushFrontLinkTable)(struct LinkTable*, EleType);

typedef EleType (*GetElementLinkTable)(struct LinkTable*, int);

typedef bool (*RemoveElementLinkTable)(struct LinkTable*, EleType);

typedef int (*GetLenLinkTable)(struct LinkTable*);

typedef bool (*InsertElemnetLinkTable)(struct LinkTable*, int, EleType);

typedef void (*DestroyElementLinkTable)(struct LinkTable*);

typedef void (*DisplayLinkTable)(struct LinkTable*);

typedef struct LinkTable {
    LinkNode *head;

    PushBackLinkTable push_back;
    PushFrontLinkTable push_front;
    GetElementLinkTable get;
    RemoveElementLinkTable remove;
    GetLenLinkTable len;
    InsertElemnetLinkTable insert;
    DisplayLinkTable display;
    DestroyElementLinkTable destroy;
} LinkTable;


bool push_back(LinkTable *table, EleType ele) {
    LinkNode *new_node = create_node(ele);
    if (new_node == NULL) {
        return false;
    }
    
    if (table->head == NULL) {
        table->head = new_node;
    } else {
        LinkNode *current = table->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    return true;
}


bool push_front(LinkTable *table, EleType ele) {
    LinkNode *_new = create_node(ele);
    if (_new == NULL) {
        return false;
    }

    _new->next = table->head;
    table->head = _new;
    return true;
}


int len(LinkTable *table) {
    int _count = 0;
    LinkNode *current = table->head;
    while (current != NULL) {
        _count++;
        current = current->next;
    }
    return _count;
}


bool insert(LinkTable *table, int pos, EleType ele) {
    if (pos < 0 || pos > table->len(table)) {
        fprintf(stderr, "Invalid Parameters\n");
        return false;
    }

    LinkNode *_new = create_node(ele);
    if (_new == NULL) {
        return false;
    }

    if (pos == 0) {
        _new->next = table->head;
        table->head = _new;
        return true;
    }

    int _count = 0;
    LinkNode *current = table->head;
    while (current != NULL && _count < pos - 1) {
        _count++;
        current = current->next;
    }

    _new->next = current->next;
    current->next = _new;
    return true;
}



EleType get(LinkTable *table, int pos) {
    if ((pos > table->len(table)) || 
        pos < 0 || table->head == NULL) {
            
            fprintf(stderr, "Invailid Paraments\n");
            return 0;
        }

    int _count = 0;
    LinkNode *current = table->head;
    while (current != NULL && _count < pos) {
        _count++;
        current = current->next;
    }
    return current->data;  
}


void display(LinkTable *table) {
    LinkNode *current = table->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    puts("NULL");
}


void destroy(LinkTable *table) {
    LinkNode *current = table->head;
    while (current != NULL) {
        LinkNode *_tmp = current->next;
        free(current);
        current = _tmp;
    }
    table->head = NULL;
}


LinkTable create_table() {
    LinkTable table;
    table.head = NULL;
    table.push_back = push_back;
    table.push_front = push_front;
    table.len = len;
    table.get = get;
    table.insert = insert;
    table.display = display;
    table.destroy = destroy;
    return table;
}


int main() {
    LinkTable table = create_table();

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

    table.destroy(&table);
    table.display(&table);
    printf("length: %d\n", table.len(&table));

    return 0;
}
