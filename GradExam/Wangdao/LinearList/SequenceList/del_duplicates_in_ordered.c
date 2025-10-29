/* 题目信息
    从有序顺序表中删除所有其值重复的元素，使表中所有元素的值均不同。
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


void DeleteDuplicatesInOrdered(SeqList* sl) {

    // 如果顺序表为空或顺序表中仅存在一个元素，则直接退出算法
    if (sl->len <= 1) {
        return;
    }

    // 定义一个索引指针用于计算 原地构建无重复元素顺序表 的长度
    // 此处因为是有序顺序表则第一个元素可视为非重复的，则新表长度可以设为 1
    int realIndex = 1;

    // 对于具有一个以上元素的有序顺序表遍历查找非重复元素 
    // 由于顺序表有序，则直接将旧表中每个元素与新表中最后一个元素对比
    // 再将不相同元素加入新表 然后更新新表长度
    for (int i = 1; i < sl->len; i++) {
        if (sl->data[realIndex - 1] != sl->data[i]) {
            sl->data[realIndex++] = sl->data[i];
        }
    }

    // 更新去重后的顺序表长度
    sl->len = realIndex;
}



/* 
    算法实现如上，其中：
    
    时间复杂度为 O(n)	------需要循环 n - 1 次遍历整个顺序表中的元素
    
    空间复杂度为 O(1)	------算法不存在递归，且使用了常数个存储空间 realIndex 存储新表长度
    
    算法思想：
        对于空的或者只有一个元素的顺序表，无需去重，则算法直接返回，如果有序顺序表存在一个以上元素
        则易知重复元素在有序顺序表中的位置相邻，则我们可设立指针 realIndex 在遇到第一个与表尾不同的
        元素时将其添加到新表中，由此完成去重，且得到的新表也应是一个有序顺序表
	
	测试数据：
        空表或只有一个元素的有序顺序表进入算法直接退出

        所有元素相同的顺序表进入算法后 realIndex 将始终指向顺序表的第一个元素，在循环结束后直接原地修改
        输入顺序表的长度为 1

        输入一般情况下的有序顺序表执行删除：
        输入顺序表：[ 1, 2, 2, 3, 4, 4, 5 ]
        预期处理后顺序表：[ 1, 2, 3, 4, 5 ]

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
    int arr[] = { 1, 2, 2, 3, 4, 4, 5 };
    int len = sizeof(arr) / sizeof(arr[0]);
    SeqList sl;

    for (int i = 0; i < len; i++) {
        sl.data[i] = arr[i];
    }

    sl.len = len;

    SeqListPrintln(&sl);

    DeleteDuplicatesInOrdered(&sl);

    SeqListPrintln(&sl);
}

