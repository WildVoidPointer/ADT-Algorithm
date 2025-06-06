#include "sparse_matrix_compress.h"
#include <stdio.h>


SparseMatrixEleType ORIGIN_SPARSE_MATRIX[5][5] = {
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 7},
    {1, 0, 0, 0, 0},
    {0, 0, 0, 5, 0},
    {0, 2, 0, 0, 0}
};


int main() {
    SparseMatrixEleType fiducial = 0;
    int origin_rows = 5;

    SparseMatrixBean* compressed = 
        sparse_matrix_compress_of_stack(&fiducial, origin_rows, ORIGIN_SPARSE_MATRIX);

    SparseMatrixEleType** uncompressed = sparse_matrix_uncompress(&fiducial, compressed);

    sparse_matrix_uncompressed_bean_display(origin_rows, uncompressed);
    
    sparse_matrix_compressed_bean_display(compressed);

    sparse_matrix_compressed_bean_clean(&compressed);

    sparse_matrix_uncompressed_bean_clean(origin_rows, &uncompressed);

    printf("%p\n", uncompressed);
}
