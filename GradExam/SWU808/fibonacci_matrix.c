/* 题目信息
已知斐波那契数列的矩阵表示形式为：
```
[ F(n+1)  F(n)   ]   =   [ 1  1 ] ^ n
[ F(n)    F(n-1) ]       [ 1  0 ]
```
其中，`F(0) = 0, F(1) = 1`。

现给定一个正整数 `n`（`n ≥ 0`），请你实现一个算法，
计算矩阵 `[1, 1; 1, 0]` 的 `n` 次幂，并返回结果矩阵
常用数据结构的常用操作可直接使用，但需要说明对应算法的执行过程
*/



/* -----------------------------以下为作答部分---------------------------------- */

#include <stdio.h>

// 将二维数组表示的矩阵乘法单独实现
void FibMatrixMultiply(int (*result)[2], int (*base)[2]) {

    // 建立一个矩阵临时存储结果
    int temp[2][2];

    // 进行矩阵乘法
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {

            temp[i][j] = 0;

            for (int k = 0; k < 2; k++) {
                temp[i][j] += base[i][k] * result[k][j];
            }

        }
    }

    // 将临时矩阵写回
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = temp[i][j];
        }
    } 
}


// 使用 二维数组 存储计算斐波那契数列的初始矩阵
void FibMatrixPower(int (*result)[2], int n) {

    // 处理无效输入
    if (n < 0) {
        return;
    }

    // 如果指数 n = 0，返回单位矩阵
    if (n == 0) {
        result[0][0] = 1; result[0][1] = 0;
        result[1][0] = 0; result[1][1] = 1;
        return;
    }

    // 初始化 result 为斐波那契基础矩阵
    result[0][0] = 1;
    result[0][1] = 1;
    result[1][0] = 1;
    result[1][1] = 0;


    // n=1 直接返回基础矩阵
    if (n == 1) {
        return;
    }
    
    // 快速幂计算：实际计算 n - 1 次幂
    // 因为：M^n = M × M^(n - 1)，而我们已经初始化了 M
    int power = n - 1;

    int base[2][2] = {{1, 1}, {1, 0}};
    
    while (power > 0) {

        if (power & 1) {
            FibMatrixMultiply(result, base);
        }

        FibMatrixMultiply(base, base);

        power >>= 1;
    }

}



/* 
    算法实现如上，其中：
    
    时间复杂度为 O(log n)
        矩阵乘法因为矩阵固定为 2 x 2，算法时间复杂度为 O(1)
        使用了快速幂算法，算法时间复杂度为 log n
        则整体时间复杂度为 log n
        

    空间复杂度为 O(1)	
        使用了固定大小的辅助矩阵    


    算法思想：
        当 n = 0 时返回单位矩阵，k = 1 时返回基础矩阵，k > 1 时使用快速幂计算
        使用矩阵快速幂算法，通过指数的二进制分解将时间复杂度从 O(n) 优化到 O(log n)
        

	测试数据:
        x = -1 不进行计算，算法直接返回
        x = 1 预期处理结果矩阵 [[1, 1], [1, 0]]
        x = 2 预期处理结果矩阵 [[2, 1], [1, 1]]
        x = 3 预期处理结果矩阵 [[3, 2], [2, 1]]
 */


/* -----------------------------作答部分结束---------------------------------- */


// 测试主函数 此处不出现在真实考场答案中

void FibMatrixPrint(int (*matrix)[2]) {
    printf("{ ");
    for (int i = 0; i < 2; i++) {
        printf("{ ");
        for (int j = 0; j < 2; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("}, ");
    }
    printf("}\n");
}

int main() {

    int matrix[2][2] = {
        {1, 1},
        {1, 0}
    };

    FibMatrixPrint(matrix);

    FibMatrixPower(matrix, 2);

    FibMatrixPrint(matrix);

    return 0;
}
