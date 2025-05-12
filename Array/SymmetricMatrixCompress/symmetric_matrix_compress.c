#include "symmetric_matrix_compress.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


SymmetricMatrixBean* 
symmetric_matrix_compress(
    int rows, SymmetricMatrixBean (*uncompressed)[rows]) {

    if (uncompressed == NULL || rows < 0) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }
        
    SymmetricMatrixBean* compressed = 
        (SymmetricMatrixBean*) malloc 
            (sizeof(SymmetricMatrixBean) * (rows + 1) * (rows) / 2);

    if (compressed == NULL) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_INIT_ERROR);
        return NULL;
    }

    int compressed_offset = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            compressed[compressed_offset++] = uncompressed[i][j];
        }
    }
    return compressed;
}


int calculate_uncompressed_matrix_size(int compressed_size) {
    return (compressed_size >= 0) ? 
        ((int)sqrt(1 + compressed_size * 8) - 1) / 2 : -1;
}


SymmetricMatrixBean**
symmetric_matrix_uncompress(
    int compressed_size, SymmetricMatrixBean* compressed) {
    
    if (compressed == NULL || compressed < 0) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }

    int rows = calculate_uncompressed_matrix_size(compressed_size);
    if (rows == -1) {
        return NULL;
    }

    SymmetricMatrixBean** uncompressed =
        (SymmetricMatrixBean**) malloc
            (sizeof(SymmetricMatrixBean*) * rows);

    if (uncompressed == NULL) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_INIT_ERROR);
        return NULL;
    }

    int compressed_offset = 0;
    for (int i = 0; i < rows; i++) {
        uncompressed[i] = (SymmetricMatrixBean*) malloc
            (sizeof(SymmetricMatrixBean) * rows);
            
        if (uncompressed[i] == NULL) {

            fprintf(stderr, SYMMETRIC_MATRIX_BEAN_INIT_ERROR);

            for (int j = 0; j < i; j++) {
                free(uncompressed[j]);
            }
            free(uncompressed);
            return NULL;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            uncompressed[i][j] = uncompressed[j][i] 
                = compressed[compressed_offset++];
        }
    }
    
    return uncompressed;
}


int symmetric_matrix_uncompressed_bean_display(
    int rows, SymmetricMatrixBean** uncompressed) {

    if (uncompressed == NULL || *uncompressed == NULL || rows < 0) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    printf("SymmetricMatrix: {\n");
    for (int i = 0; i < rows; i++) {
        printf("    {  ");
        for (int j = 0; j < rows; j++) {
            printf("%d  ", uncompressed[i][j]);
        }
        printf("},\n");
    }
    printf("}\n");
    return 0;
}


int
symmetric_matrix_compressed_bean_display(
    int compressed_size, SymmetricMatrixBean* compressed) {

    if (compressed == NULL || compressed_size < 0) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    printf("SymmetricMatrix:  {  ");
    for (int i = 0; i < compressed_size; i++) {
        printf("%d  ", compressed[i]);
    }
    printf("}\n");
    return 0;
}


int symmetric_matrix_uncompressed_bean_clean(
    int uncompressed_size, SymmetricMatrixBean*** uncompressed) {
    
    if (uncompressed == NULL || *uncompressed == NULL || uncompressed_size < 0) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    for (int i = 0; i < uncompressed_size; i++) {
        free((*uncompressed)[i]);
    }

    free(*uncompressed);
    *uncompressed = NULL;
    return 0;
}


int symmetric_matrix_compressed_bean_clean(SymmetricMatrixBean** compressed) {
    if (compressed == NULL || *compressed == NULL) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }
    free(*compressed);
    *compressed = NULL;
    return 0;
}
