/* 题目信息

*/



/* -----------------------------以下为作答部分---------------------------------- */

#include <stdio.h>

#define MAX_LEN 100

typedef int SeqListDataType;

// 定义一个顺序表结构，len 表示顺序表的实际元素个数
typedef struct SeqList {
    SeqListDataType data[MAX_LEN];
    int len;
} SeqList;



/* 算法实现如上，其中：
    
时间复杂度为 O()



空间复杂度为 O()



算法思想



测试数据



 */


/* -----------------------------作答部分结束---------------------------------- */


// 测试主函数 此处不出现在真实考场答案中
void SeqListPrintln(SeqList* sl) {
    for (int i = 0; i < sl->len; i++) {
        printf("%d  ", sl->data[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = { 2, 4, 3, 4, 4, 6, 7, 8 };
    int len = sizeof(arr) / sizeof(arr[0]);
    SeqList sl;

    for (int i = 0; i < len; i++) {
        sl.data[i] = arr[i];
    }

    sl.len = len;

    SeqListPrintln(&sl);


    SeqListPrintln(&sl);
}

