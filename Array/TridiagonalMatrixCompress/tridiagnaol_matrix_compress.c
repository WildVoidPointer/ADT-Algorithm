#include "tridiagonal_matrix_compress.h"
#include <stdio.h>
#include <stdlib.h>

TridiagonalMatrixBean*
tridiagnaol_matrix_compress_of_stack(
    int rows, TridiagonalMatrixBean (*uncompressed)[rows]) {
    
    if (uncompressed == NULL || rows < 0) {
        fprintf(stderr, TRIDIAGNAOL_MATRIX_ACCESS_ERROR);
        return NULL;
    }

    int compressed_bean_size = rows + (rows - 1) * 2;

    TridiagonalMatrixBean* compressed =
        (TridiagonalMatrixBean*) malloc (sizeof(TridiagonalMatrixBean) * compressed_bean_size);
    
    if (compressed == NULL) {
        fprintf(stderr, TRIDIAGNAOL_MATRIX_BEAN_INIT_ERROR);
        return NULL;
    }

    int compressed_offset = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (abs(i - j) <= 1) {
                compressed[compressed_offset++] = uncompressed[i][j];
            }
        }
    }

    return compressed;
}