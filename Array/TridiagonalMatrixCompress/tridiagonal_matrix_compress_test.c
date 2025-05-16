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

    TridiagonalMatrixBean* compressed = tridiagonal_matrix_compress_of_stack(
        origin_matrix_rows, ORIGIN_MATRIX
    );

    tridiagonal_matrix_compressed_bean_display(compressed_size, compressed);

    TridiagonalMatrixBean** uncompressed =  tridiagonal_matrix_uncompress(compressed_size, compressed);

    tridiagonal_matrix_uncompressed_bean_display(origin_matrix_rows, uncompressed);

    TridiagonalMatrixBean* compressed2 = tridiagonal_matrix_compress_of_heap(
        origin_matrix_rows, uncompressed
    );

    tridiagonal_matrix_compressed_bean_display(compressed_size, compressed2);

    tridiagonal_matrix_compressed_bean_clean(&compressed);

    tridiagonal_matrix_compressed_bean_clean(&compressed2);

    tridiagonal_matrix_uncompressed_bean_clean(origin_matrix_rows, &uncompressed);

    printf("%p\n", compressed);
}

