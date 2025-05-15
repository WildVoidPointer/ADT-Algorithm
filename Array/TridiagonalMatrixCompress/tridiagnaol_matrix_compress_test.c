#include "tridiagonal_matrix_compress.h"

TridiagonalMatrixBean ORIGIN_MATRIX [5][5] = {
    {1, 2, 0, 0, 0},
    {3, 4, 5, 0, 0},
    {0, 6, 7, 8, 0},
    {0, 0, 9, 10, 11},
    {0, 0, 0, 12, 13}
};


int main() {
    int origin_matrix_rows = 5;
    int compressed_size = 13;

    TridiagonalMatrixBean* compressed = tridiagnaol_matrix_compress_of_stack(
        origin_matrix_rows, ORIGIN_MATRIX
    );

    tridiagnaol_matrix_compressed_bean_display(compressed_size, compressed);

    tridiagnaol_matrix_compressed_bean_clean(&compressed);

    printf("%p\n", compressed);
}

