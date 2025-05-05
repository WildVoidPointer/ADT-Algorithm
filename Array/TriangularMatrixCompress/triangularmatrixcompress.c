#include "triangularmatrixcompress.h"
#include <stdio.h>
#include <stdlib.h>


TriangularMatrixBean*
lower_triangular_matrix_compress(int rows, TriangularMatrixBean (*uncompressed)[rows]) {
    if (uncompressed == NULL) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }
    TriangularMatrixBean* compressed = 
        (TriangularMatrixBean*) 
            malloc (sizeof(TriangularMatrixBean) * (rows + 1) * (rows) / 2 + 1);
    
    if (compressed == NULL) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_INIT_ERROR);
        return NULL;
    }

    int compressed_offset = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            compressed[compressed_offset++] = uncompressed[i][j];
        }
    }
    compressed[compressed_offset] = uncompressed[0][rows - 1];
    return compressed;
}


int 
triangular_matrix_flat_bean_clean(TriangularMatrixBean** compressed) {
    if (compressed == NULL || *compressed == NULL) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    free(*compressed);
    *compressed = NULL;
    return 0;
}
