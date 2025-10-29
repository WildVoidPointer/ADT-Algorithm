/* 题目信息
    从顺序表中删除其值在给定值 $s$ 和 $t$ 之间（包含 $s$ 和 $t$，要求 $s<t$）的所有元素，
    若 $s$ 或 $t$ 不合理或顺序表为空，则显示出错信息并退出运行。
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


void DeleteElementsWithinRange(SeqList* sl, SeqListDataType s, SeqListDataType t) {

    // 如果输入顺序表为空表或输入 s 和 t 不合法，则直接返回
    if (sl->len <= 0) {
        printf("error: the SeqList is empty\n");
        return;
    }

    if (s >= t) {
        printf("error: the range is invalid\n");
        return;
    }

    // 定义一个索引指针 用于原地修改时存储由非删除元素组成的顺序表的实际长度
    int realIndex = 0;

    // 遍历查找非删除元素 并且将其存储到索引指针位置实现原地修改，最后更新索引指针
    for (int i = 0; i < sl->len; i++) {
        if (sl->data[i] < s || sl->data[i] > t) {
            sl->data[realIndex++] = sl->data[i];
        }
    }

    // 更新顺序表长度为实际未删除元素组成的新顺序表的长度
    sl->len = realIndex;
}



/* 
    算法实现如上，其中：
    
    时间复杂度为 O(n)	------因为需要循环 n 次，用于遍历查找每一个在删除范围之外的元素
    
    空间复杂度为 O(1)	------算法中不存在递归，且仅使用了常数个存储空间存储 i 与 realIndex
    
    算法思想：
        对于空顺序表和 s 不小于 t 的情况分别进行判断后输出对应的错误信息后退出，然后使用 realIndex 存储
        在原地构建删除范围之外元素构成的新顺序表的长度，最后修改输入顺序表的长度为 realIndex 的值，
        以达到原地修改的效果
	
	测试数据
        输入空顺序表：[  ]
        预期输出：error: the SeqList is empty

        输入 s 大于或等于 t (即 s 和 t 不合法的情况)
        预期输出：error: the range is invalid

        输入合法的顺序表、s、t
        输入顺序表：[ 2, 4, 3, 4, 4, 6, 7, 8 ]
        s = 2 、 t = 6
        处理后顺序表：[ 7, 8 ]

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

    DeleteElementsWithinRange(&sl, 2, 6);

    SeqListPrintln(&sl);
}
