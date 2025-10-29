/* 题目信息
    在带头结点的单链表 $L$ 中，删除所有值为 $x$ 的结点，并释放其空间，
    假设值为 $x$ 的结点不唯一，试编写算法以实现上述操作。
*/



/* -----------------------------以下为作答部分---------------------------------- */

#include <stdio.h>
#include <stdlib.h>


typedef int LinkedListNodeDataType;

typedef struct LinkedListNode {
    LinkedListNodeDataType data;
    struct LinkedListNode* next;  
} LinkedListNode;


void DeleteAllSpecialElements(LinkedListNode* head, LinkedListNodeDataType x) {

    // 如果带头节点链表为空 直接退出算法
    if (head->next == NULL) {
        return;
    }

    // 定义两个节点指针 一个存储上一个节点 一个存储当前节点
    LinkedListNode* prevNode = head;
    LinkedListNode* currNode = head->next;

    // 从链表的第一个节点开始遍历查找需要删除的节点
    while (currNode !=  NULL) {

        // 如果该节点不符合删除要求 同步更新上一个节点与当前节点指针
        // 否则将上一个节点的 next 更新为当前节点的下一个节点 然后释放当前节点 
        // 再将当前节点指针指向未删除前链表的下一个节点
        if (currNode->data != x) {
            prevNode = currNode;
            currNode = currNode->next;
        } else {
            prevNode->next = currNode->next;
            free(currNode);
            currNode = prevNode->next;
        }
    }
}



/* 
    算法实现如上，其中：
    
    时间复杂度为 O(n)	------需要循环 n 次以遍历输入链表
    
    空间复杂度为 O(1)	------使用了常数个变量 prevNode 与 currNode 指针
    
    算法思想：
        对于输入的链表为空表时，直接退出算法，如果输入链表非空，则设立两个指针，
        一个指向当前节点，一个指向当前节点的上一个节点，以保证删除当前节点时
        可以直接找到当前节点的上一个节点，通过调整 prevNode 指针的 next 
        保存当前节点的下一个节点地址，然后释放当前节点内存，然后再通过 prevNode
        指针获取删除前链表的下一个节点，以保证能够正确更新链表节点的前后关系
	
	测试数据：
        如果传入链表为空链表，将直接退出算法

        如果传入链表只有一个节点，则在循环中比较一次后根据实际情况进行删除或保持原样后退出

        如果传入链表的每个元素都是 x ，则 prevNode 将因循环条件固定在 head 头节点，直至删除所有节点

        如果传入链表中仅有部分元素是 x，则正常进行循环，在 currNode 为 NULL 时退出算法
        输入链表：[ 1, 4, 4, 3, 6, 7, 8, 9 ]
        x = 4
        预期处理后的链表：[ 1, 3, 6, 7, 8, 9 ]

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
    int arr[] = { 1, 4, 4, 3, 6, 7, 8, 9 };
    int len = sizeof(arr) / sizeof(arr[0]);

    LinkedListNode* head = createLinkedListFromArray(arr, len);

    printLinkedList(head);

    DeleteAllSpecialElements(head, 4);

    printLinkedList(head);
}
