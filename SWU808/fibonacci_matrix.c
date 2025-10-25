/* 题目信息
已知斐波那契数列的矩阵表示形式为：
```
[ F(n+1)  F(n)   ]   =   [ 1  1 ] ^ n
[ F(n)    F(n-1) ]       [ 1  0 ]
```
其中，`F(0) = 0, F(1) = 1`。

现给定一个正整数 `k`（`k ≥ 0`），请你实现一个算法，
计算矩阵 `[1, 1; 1, 0]` 的 `k` 次幂，并返回结果矩阵
常用数据结构的常用操作可直接使用，但需要说明对应算法的执行过程
*/



/* -----------------------------以下为作答部分---------------------------------- */

#include <stdio.h>

// 将二维数组表示的矩阵乘法单独实现
void MatrixMultiply(int (*result)[2], int (*base)[2]) {

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

    // 将临时矩阵写回 result
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = temp[i][j];
        }
    } 
}


// 使用 二维数组 存储计算斐波那契数列的初始矩阵
void MatrixPower(int (*result)[2], int n) {

    // 如果传入的次方数 n 小于 0 则不进行计算，算法直接返回
    if (n < 0) {
        return;
    }

    // 如果传入 n 等于 0 则直接修改结果矩阵为单位矩阵
    if (n == 0) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (i == j) {
                    result[i][j] = 1;
                } else {
                    result[i][j] = 0;
                }
            }
        }
    }

    // 初始化 result 矩阵为斐波那契数列的单位矩阵
    result[0][0] = 1;
    result[0][1] = 1;
    result[1][0] = 1;
    result[1][1] = 0;


    // 如果传入 n 为 1 则直接返回
    if (n == 1) {
        return;
    }

    // 建立斐波那契数列的单位矩阵
    int unit[2][2] = {
        {1, 1},
        {1, 0}
    };

    // 对单位矩阵执行矩阵快速幂
    while (n != 0) {

        if (n & 1) {
            MatrixMultiply(result, unit);
        }

        MatrixMultiply(unit, unit);

        n = n >> 1;
    }
    
}



/* 
    算法实现如上，其中：
    
    时间复杂度为 O(log_2 n)	
        因为输入数据的特殊性，算法中的矩阵乘法和单位矩阵修改实际上是常数次，
        故算法的时间复杂度取决与传入的次方数 n，而对于矩阵求幂，我们使用了
        快速幂算法，快速幂算法基于二进制分解，故每次循环后问题规模减半，故
        时间复杂度为 O(log_2 n)
        
    
    空间复杂度为 O(1)	
        算法中建立了一个 2 x 2 矩阵，使用了常数个存储空间
    
    算法思想：
        
    
	测试数据:
        输入初始矩阵：[[1, 1], [1, 0]]  x = 1 则原样不动直接返回

        输入初始矩阵：[[1, 1], [1, 0]]  x = 2 
        预期处理结果矩阵 [[2, 1], [1, 1]]
 */


/* -----------------------------作答部分结束---------------------------------- */


// 测试主函数 此处不出现在真实考场答案中

void FibonacciMatrixPrint(int (*matrix)[2]) {
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

    FibonacciMatrixPrint(matrix);

    MatrixPower(matrix, 2);

    FibonacciMatrixPrint(matrix);

    return 0;
}
