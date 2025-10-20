#include <stdio.h>
#include <stdlib.h>


typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;


int search_linked_list_cycle_origin(ListNode* cycle_list);


ListNode* createCircularLinkedList(int size, int loopPos);


int main() {
    int cycle_list_size = 13;
    int default_cycle_origin = 5;
    ListNode* cycle_list = createCircularLinkedList(cycle_list_size, default_cycle_origin);

    int search_result = search_linked_list_cycle_origin(cycle_list);

    printf("The starting point of the cycle list is :  %d\n", search_result);
    return 0;
}


int search_linked_list_cycle_origin(ListNode* cycle_list) {
    ListNode* fast_ptr = cycle_list;
    ListNode* slow_ptr = cycle_list;

    while (fast_ptr != NULL || fast_ptr->next !=  NULL) {
        slow_ptr = slow_ptr->next;
        fast_ptr = fast_ptr->next->next;

        if (fast_ptr == slow_ptr) {
            break;
        }
    }

    ListNode* locate_ptr = cycle_list;
    int starting_point_pos = 1;

    while (locate_ptr != slow_ptr) {
        starting_point_pos++;
        locate_ptr = locate_ptr->next;
        slow_ptr = slow_ptr->next;
    }
    
    return starting_point_pos;
}


ListNode* createCircularLinkedList(int size, int loopPos) {
    if (size <= 0) return NULL;
    
    // 创建头节点
    ListNode *head = (ListNode*)malloc(sizeof(ListNode));
    head->val = 0;
    ListNode *current = head;
    
    // 创建中间节点
    for (int i = 1; i < size; i++) {
        current->next = (ListNode*)malloc(sizeof(ListNode));
        current = current->next;
        current->val = i;
    }
    
    // 找到环的入口节点
    ListNode *loopEntry = head;
    for (int i = 0; i < loopPos && loopEntry->next != NULL; i++) {
        loopEntry = loopEntry->next;
    }
    
    // 形成环
    current->next = loopEntry;
    
    return head;
}
