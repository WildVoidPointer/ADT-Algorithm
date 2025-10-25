#include <stdio.h>


void square_matrix_multiply(
    int row, int (*m1)[row], int (*m2)[row]
) {

    int temp[row][row];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {

            temp[i][j] = 0;

            for (int k = 0; k < row; k++) {
                temp[i][j] += m1[i][k] * m2[k][j];
            }

        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            m1[i][j] = temp[i][j];
        }
    } 
}


void square_matrix_copy(
    int row, int (*origin)[row], int (*result)[row]
) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            result[i][j] = origin[i][j];
        }
    }
}


void to_unit_matrix(int row, int (*matrix)[row]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            if (i == j) {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }
}


void square_matrix_fast_power(
    int row, int (*base)[row], 
    int (*result)[row], int n
) {

    if (n < 0) {
        return;
    }

    if (n == 1) {
        square_matrix_copy(row, base, result);
        return;
    }

    to_unit_matrix(row, result);

    if (n == 0) {
       return;
    }

    int temp_base[row][row];

    square_matrix_copy(row, base, temp_base);

    while (n != 0) {

        if (n & 1) {
            square_matrix_multiply(row, result, temp_base);
        }

        square_matrix_multiply(row, temp_base, temp_base);

        n = n >> 1;
    }
}


void square_matrix_print(int row, int (*matrix)[row]) {
    printf("{ ");
    for (int i = 0; i < row; i++) {
        printf("{ ");
        for (int j = 0; j < row; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("}%s", (i == row - 1) ? " " : ", ");
    }
    printf("}\n");
}


int main() {
    const int row = 4;

    int matrix[][4] = {
        {1, 9, 9, 9},
        {2, 3, 9, 9},
        {4, 5, 6, 9},
        {7, 8, 9, 10}
    };

    int result[row][4];

    square_matrix_print(row, matrix);

    square_matrix_fast_power(row, matrix, result, 2);

    /* if n = 2 , result: { 
            { 118 153 225 261 }, 
            { 107 144 180 216 },
            { 101 153 198 225 },
            { 129 212 279 316 } 
        }
    */
    square_matrix_print(row, result);

    return 0;
}
