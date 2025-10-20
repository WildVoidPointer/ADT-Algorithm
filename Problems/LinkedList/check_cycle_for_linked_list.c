#include <stdio.h>
#include <stdlib.h>


typedef struct LinkedListNode {
    int data;
    struct LinkedListNode* next;
} LinkedListNode;


int check_cycle_for_linked_list(LinkedListNode* head);


LinkedListNode* createAcyclicLinkedList(int arr[], int size);


LinkedListNode* createCyclicLinkedList(int arr[], int size, int loopPos);


int main() {
    int arr[] = {1, 2, 3, 4, 5};
    LinkedListNode* acyclicList = createAcyclicLinkedList(arr, 5);
    LinkedListNode* cyclicList = createCyclicLinkedList(arr, 5, 2);

    if (check_cycle_for_linked_list(acyclicList)) {
        printf("This acyclicList has a loop structure\n");
    }

    if (check_cycle_for_linked_list(cyclicList)) {
        printf("This cyclicList has a loop structure\n");
    }

    return 0;
}


int check_cycle_for_linked_list(LinkedListNode* head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }

    LinkedListNode* fast_ptr = head->next;
    LinkedListNode* slow_ptr = head;

    while (slow_ptr != fast_ptr) {
        if (fast_ptr == NULL || fast_ptr->next == NULL) {
            return 0;
        }
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;
    }

    return 1;
}


// 创建无环链表
LinkedListNode* createAcyclicLinkedList(int arr[], int size) {
    if (size == 0) return NULL;
    
    LinkedListNode* head = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    head->data = arr[0];
    head->next = NULL;
    
    LinkedListNode* current = head;
    
    for (int i = 1; i < size; i++) {
        LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        newNode->data = arr[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
    
    return head;
}


// 创建有环链表
LinkedListNode* createCyclicLinkedList(int arr[], int size, int loopPos) {
    if (size == 0) return NULL;
    
    LinkedListNode* head = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    head->data = arr[0];
    head->next = NULL;
    
    LinkedListNode* current = head;
    LinkedListNode* loopNode = (loopPos == 0) ? head : NULL;
    
    for (int i = 1; i < size; i++) {
        LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        newNode->data = arr[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
        
        if (i == loopPos) {
            loopNode = newNode;
        }
    }
    
    // 创建环
    if (loopPos >= 0 && loopPos < size) {
        current->next = loopNode;
    }
    
    return head;
}
