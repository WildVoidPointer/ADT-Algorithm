/* 题目信息
    设计一个 高效算法 ，将顺序表 $L$ 的所有元素逆置，要求算法的空间复杂度为 $O(1)$。
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

void ReverseSeqList(SeqList* sl) {

    // 如果输入顺序表是一个空表或者顺序表只有一个元素 则直接返回
    if (sl->len <= 1) {
        return;
    }

    // 如果顺序表的长度大于 1 则以顺序中间位置为界将左右两端元素逐一交换
    int midPos = sl->len / 2;

    for (int i = 0; i < midPos; i++) {
        SeqListDataType tmp = sl->data[i];
        sl->data[i] = sl->data[sl->len - 1 - i];
        sl->data[sl->len - 1 - i] = tmp;
    }
}



/* 
    算法实现如上，其中：
    时间复杂度为 O(n)   ------执行循环 n / 2 次
    空间复杂度为 O(1)   ------使用常数个辅助变量

    算法思想：双指针从两端向中间交换元素
	
	如果输入的顺序表是空表或元素只有一个的顺序表 则直接返回无需进行翻转
    输入顺序表：[ ]
    翻转后顺序表：[ ]
    输入顺序表：[ 1 ]
    翻转后顺序表：[ 1 ]

    如果输入顺序表具有多个元素 则以其中间位置元素为界 翻转顺序表 
    如下顺序表将以 5 为界 通过交换两端元素位置翻转顺序表
    输入顺序表：[ 1, 3, 6, 5, 7, 8, 9 ]
    翻转后顺序表：[ 9, 8, 7, 5, 6, 3, 1 ]

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
    int arr[] = {1, 3, 6, 5, 7, 8, 9};
    int len = sizeof(arr) / sizeof(arr[0]);
    SeqList sl;

    for (int i = 0; i < len; i++) {
        sl.data[i] = arr[i];
    }

    sl.len = len;

    SeqListPrintln(&sl);

    ReverseSeqList(&sl);

    SeqListPrintln(&sl);
}
