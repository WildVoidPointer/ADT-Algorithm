// 题目信息
// 从顺序表中删除具有最小值的元素（假设唯一）并由函数返回被删除元素的值。空出的位
// 置由最后一个元素填补, 若顺序表为空, 则显示出错信息并退出运行


/* -----------------------------以下为作答部分---------------------------------- */

#include <stdio.h>

#define MAX_LEN 100

// 定义一个基准的无效值 增强顺序表的健壮性
#define INVALID_VALUE 0

typedef int SeqListDataType;

// 定义一个顺序表结构，len 表示顺序表的实际元素个数
// 且保证初始化后空表起始长度 len 为 0
typedef struct SeqList {
    int data[MAX_LEN];
    int len;
} SeqList;

SeqListDataType DeleteAndReturnMinElement(SeqList* sl) {

    // 如果顺序表为空 打印错误信息
    if (sl->len <= 0) {
        printf("error: the SeqList is empty");
        return -1;
    }

    // 选择非空顺序表的第一个元素作为基准
    SeqListDataType min_item = sl->data[0];

    // 记录最小元素在顺序表中数组的实际索引位置
    int index = 0;

    // 从第二个元素开始按顺序查找最小值元素
    for (int i = 1; i < sl->len; i++) {
        if (sl->data[i] < min_item) {
            min_item = sl->data[i];
            index = i;
        }
    }

    // 如果最小元素是最后一个 将其直接标记为无效值
    // 将最后一个值赋值到最小元素的位置 并将最后一个元素标记为无效值
    if (index == sl->len - 1) {
        sl->data[index] = INVALID_VALUE;
    } else {
        sl->data[index] = sl->data[sl->len - 1];
        sl->data[sl->len - 1] = INVALID_VALUE;
    }

    sl->len--;

    // 返回最小值
    return min_item;
}

/* 
    算法实现如上，其中：
    由于此处只进行了单重循环，且循环在最坏条件下的次数为 n ，
    使用了两个个局部变量存储最小元素和最小元素的位置则

    时间复杂度为 O(n)
    空间复杂度为 O(1)

    若输入的线性表数据为：[1, 4, 5, 0, 6, 9]
    则预期处理后的结果应为： [1, 4, 5, 6, 9]

 */


/* -----------------------------作答部分结束---------------------------------- */

// 测试主函数 此处不出现在真实考场答案中
int main() {
    SeqList sl;
    sl.len = 0;

    for (int i = 8; i > 0; i--) {
        sl.data[sl.len] = i;
        sl.len++;
    }

    printf("SeqList len: %d , The last item: %d\n", sl.len, sl.data[sl.len - 1]);

    printf("The min item: %d\n", DeleteAndReturnMinElement(&sl));

    printf("SeqList len: %d , The last item: %d\n", sl.len, sl.data[sl.len - 1]);

}
