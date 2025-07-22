#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedListNode {
    int data;
    struct LinkedListNode* next;
} LinkedListNode;


LinkedListNode* 
merge_orderly_linked_list (LinkedListNode* head1, LinkedListNode* head2);


LinkedListNode* createList1();


LinkedListNode* createList2();


void print_list(LinkedListNode* head);


int main() {
    LinkedListNode* list1 = createList1();
    LinkedListNode* list2 = createList2();
    
    LinkedListNode* res = merge_orderly_linked_list(
        list1, list2
    );

    print_list(res);
    
    return 0;
}



LinkedListNode* 
merge_orderly_linked_list (LinkedListNode* head1, LinkedListNode* head2) {
    LinkedListNode* head1_ptr = head1;
    LinkedListNode* head2_ptr = head2;
    LinkedListNode dummy_node;
    LinkedListNode* current = &dummy_node;

    while (head1_ptr != NULL && head2_ptr != NULL) {
        if (head1_ptr->data > head2_ptr->data) {
            current->next = head2_ptr;
            head2_ptr = head2_ptr->next;
        } else {
            current->next = head1_ptr;
            head1_ptr = head1_ptr->next;
        }

        current = current->next;
    } 

    if (head1_ptr == NULL) {
        current->next = head2_ptr;
    } else {
        current->next = head1_ptr;
    }

    return dummy_node.next;
}


// 创建链表1: 1 -> 3 -> 5 -> 7 -> NULL
LinkedListNode* createList1() {
    LinkedListNode* head = NULL;
    LinkedListNode* temp = NULL;
    
    // 创建节点1
    LinkedListNode* node1 = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node1->data = 1;
    node1->next = NULL;
    head = node1;
    temp = node1;
    
    // 创建节点2
    LinkedListNode* node2 = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node2->data = 3;
    node2->next = NULL;
    temp->next = node2;
    temp = node2;
    
    // 创建节点3
    LinkedListNode* node3 = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node3->data = 5;
    node3->next = NULL;
    temp->next = node3;
    temp = node3;
    
    // 创建节点4
    LinkedListNode* node4 = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node4->data = 7;
    node4->next = NULL;
    temp->next = node4;
    
    return head;
}

// 创建链表2: 2 -> 4 -> 6 -> 8 -> NULL
LinkedListNode* createList2() {
    LinkedListNode* head = NULL;
    LinkedListNode* temp = NULL;
    
    // 创建节点1
    LinkedListNode* node1 = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node1->data = 2;
    node1->next = NULL;
    head = node1;
    temp = node1;
    
    // 创建节点2
    LinkedListNode* node2 = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node2->data = 4;
    node2->next = NULL;
    temp->next = node2;
    temp = node2;
    
    // 创建节点3
    LinkedListNode* node3 = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node3->data = 6;
    node3->next = NULL;
    temp->next = node3;
    temp = node3;
    
    // 创建节点4
    LinkedListNode* node4 = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node4->data = 8;
    node4->next = NULL;
    temp->next = node4;
    
    return head;
}


void print_list(LinkedListNode* head) {
    LinkedListNode* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
