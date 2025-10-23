/* 题目信息
    对长度为 $n$ 的顺序表 $L$，编写一个时间复杂度为 $O(n)$，空间复杂度为 $O(1)$ 的算法，该算法删除顺序表中所有值为 $x$ 的数据元素。
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


void DeleteAllSpecialElements(SeqList* sl, SeqListDataType ele) {

    // 如果顺序表为空 直接退出算法
    if (sl->len <= 0) {
        return;
    }

    // 定义一个索引指针 对已有顺序表进行原地修改
    // 用于保存顺序表中未被删除元素组成顺序表的长度
    int realIndex = 0;

    // 如果顺序表不为空则循环遍历找到非删除目标元素
    // 将其添加到 realIndex 维护的顺序表 并且同时更新索引指针 realIndex
    for (int i = 0; i < sl->len; i++) {
        if (sl->data[i] != ele) {
            sl->data[realIndex++] = sl->data[i];
        }
    }

    // 查找完成后 realIndex 恰好是新顺序表的实际长度 直接将其赋值给顺序表长度
    sl->len = realIndex;

}



/* 
    算法实现如上，其中：
    
    时间复杂度为 O(n)	------需要循环 n 次

    空间复杂度为 O(1)	------使用常数个存储空间
    
    算法思想：
        对于空表直接返回 不进行操作，而对于非空顺序表 则直接遍历查找非删除目标元素，通过维护
        一个新的索引指针 对现有顺序表进行原地修改 最后将索引指针的值赋值给现有长度 
        得到删除目标元素后的新顺序表
	
	测试数据：
        如果输入的顺序表为空表则直接返回 不进行操作

        如果输入的顺序表只有一个元素或为多个相同元素 且为删除目标 则将会清空顺序表
        输入顺序表：[ 1, 1, 1, 1 ] 或 [ 1 ]  
        x = 1   
        处理后顺序表：[  ]

        如果输入顺序表中存在部分目标元素 则将非删除目标元素原地修改为新表后返回
        输入顺序表：[ 2, 4, 3, 4, 4, 6, 7, 8 ]
        x = 4
        处理后顺序表：[ 2, 3, 6, 7, 8 ]

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

    DeleteAllSpecialElements(&sl, 4);

    SeqListPrintln(&sl);
}
