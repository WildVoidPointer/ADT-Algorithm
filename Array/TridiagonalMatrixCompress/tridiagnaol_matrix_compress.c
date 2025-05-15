#include "tridiagonal_matrix_compress.h"
#include <stdio.h>
#include <stdlib.h>


int calculate_uncompressed_matrix_size(int compressed_size) {
    return (compressed_size >= 0) ? 
        (compressed_size + 2) / 3: -1;
}


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


TridiagonalMatrixBean**
tridiagnaol_matrix_uncompress(int compressed_szie, TridiagonalMatrixBean* compressed) {

    if (compressed == NULL || compressed_szie < 0) {
        fprintf(stderr, TRIDIAGNAOL_MATRIX_ACCESS_ERROR);
        return NULL;
    }

    int rows = calculate_uncompressed_matrix_size(compressed_szie);
}


int tridiagnaol_matrix_compressed_bean_display(
    int compressed_size, TridiagonalMatrixBean* compressed) {
    
    if (compressed == NULL || compressed_size < 0) {
        fprintf(stderr, TRIDIAGNAOL_MATRIX_ACCESS_ERROR);
        return 0;
    }

    printf("TridiagnaolMatrix: {  ");
    for (int i = 0; i < compressed_size; i++) {
        printf("%d  ", compressed[i]);
    }
    printf("}\n");
    return 0;
}


int
tridiagnaol_matrix_compressed_bean_clean(TridiagonalMatrixBean** compressed) {

    if (compressed == NULL || *compressed == NULL) {
        fprintf(stderr, TRIDIAGNAOL_MATRIX_ACCESS_ERROR);
        return 0;
    }

    free(*compressed);

    *compressed = NULL;

    return 0;
}
