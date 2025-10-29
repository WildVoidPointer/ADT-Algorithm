/* 题目信息

*/



/* -----------------------------以下为作答部分---------------------------------- */

#include <stdio.h>
#include <stdlib.h>


typedef int LinkedListNodeDataType;

typedef struct LinkedListNode {
    LinkedListNodeDataType data;
    struct LinkedListNode* next;  
} LinkedListNode;




/* 算法实现如上，其中：

时间复杂度为 O()



空间复杂度为 O()



算法思想



测试数据



 */


/* -----------------------------作答部分结束---------------------------------- */


// 测试主函数 此处不出现在真实考场答案中

void printLinkedList(LinkedListNode* head) {
    LinkedListNode* current = head->next;
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf("  ");
        }
        current = current->next;
    }
    printf("\n");
}

LinkedListNode* createLinkedListFromArray(LinkedListNodeDataType arr[], int size) {
    LinkedListNode* head = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    head->next = NULL;
    LinkedListNode* tail = head;
    
    for (int i = 0; i < size; i++) {
        LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        newNode->data = arr[i];
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
    
    return head;
}

int main() {

}
