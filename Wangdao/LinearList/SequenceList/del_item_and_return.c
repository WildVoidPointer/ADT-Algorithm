// 题目信息
// 从顺序表中删除具有最小值的元素（假设唯一）并由函数返回被删除元素的值。空出的位
// 置由最后一个元素填补, 若顺序表为空, 则显示出错信息并退出运行


/* -----------------------------以下为作答部分---------------------------------- */

#include <stdio.h>
#include <stdbool.h>

#define MAX_LEN 100

typedef int SeqListDataType;

// 定义一个顺序表结构，len 表示顺序表的实际元素个数
typedef struct SeqList {
    SeqListDataType data[MAX_LEN];
    int len;
} SeqList;


// 因为当表为空时 随意返回可能会带来混淆 所以额外传递一个结果有效位
SeqListDataType DeleteAndReturnMinElement(SeqList* sl, bool* flag) {

    // 如果顺序表为空 打印错误信息 然后将 返回值有效位 置为 false
    if (sl->len <= 0) {
        printf("error: the SeqList is empty");
        *flag = false;
        return 0;
    }

    // 选择非空顺序表的第一个元素作为基准
    SeqListDataType minValue = sl->data[0];

    // 记录最小元素在顺序表中数组的实际索引位置
    int minPos = 0;

    // 如果表中元素不止一个 则从第二个元素开始按顺序查找最小值元素
    for (int i = 1; i < sl->len; i++) {
        if (sl->data[i] < minValue) {
            minValue = sl->data[i];
            minPos = i;
        }
    }

    // 如果最小元素不是最后一个元素 将最后一个元素赋值给最小值元素位置
    // 如果最小元素是最后一个元素 则直接返回
    if (minPos != sl->len - 1) {
        sl->data[minPos] = sl->data[sl->len - 1];
    }

    sl->len--;

    // 将结果有效位置为 true 并返回最小值
    *flag = true;
    return minValue;
}

/* 
    算法实现如上，其中：

    时间复杂度为 O(n) ------循环 n-1 次

    空间复杂度为 O(1) ------使用了常数个辅助变量

    算法思想：通过循环整个顺序表 记录并且操作最小元素位置

    若输入的是一个空表 直接退出算法 并打印错误信息
    输入顺序表：[]
    预期输出：error: the SeqList is empty

    若输入的是仅有一个元素的顺序表 不进入循环且直接修改顺序表长度后返回
    输入顺序表：[ 1 ]
    预期输出：1

    若输入的线性表元素不止一个 则进入循环查找
    输入顺序表：[ 1, 4, 5, 0, 6, 9 ]
    预期处理后顺序表： [ 1, 4, 5, 6, 9 ]
    预期输出为：0

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

    bool result_is_vaild = false;

    printf("SeqList len: %d , The last item: %d\n", sl.len, sl.data[sl.len - 1]);

    printf("The min item: %d\n", DeleteAndReturnMinElement(&sl, &result_is_vaild));

    printf("SeqList len: %d , The last item: %d\n", sl.len, sl.data[sl.len - 1]);

}
