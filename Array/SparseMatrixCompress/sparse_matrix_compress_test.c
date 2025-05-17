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
    
    sparse_matrix_compressed_bean_display(compressed);

    sparse_matrix_compressed_bean_clean(&compressed);

    printf("%p\n", compressed);
}
