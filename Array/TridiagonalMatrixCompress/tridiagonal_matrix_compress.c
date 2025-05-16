#include "tridiagonal_matrix_compress.h"
#include <stdio.h>
#include <stdlib.h>


int calculate_uncompressed_matrix_size(int compressed_size) {
    return (compressed_size >= 0) ? 
        (compressed_size + 2) / 3: -1;
}


TridiagonalMatrixBean*
tridiagonal_matrix_compress_of_heap(int rows, TridiagonalMatrixBean** uncompressed){
    
    if (uncompressed == NULL || *uncompressed == NULL || rows < 0) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_ACCESS_ERROR);
        return NULL;
    }

    int compressed_bean_size = rows + (rows - 1) * 2;

    TridiagonalMatrixBean* compressed =
        (TridiagonalMatrixBean*) malloc (sizeof(TridiagonalMatrixBean) * compressed_bean_size);
    
    if (compressed == NULL) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_BEAN_INIT_ERROR);
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


TridiagonalMatrixBean*
tridiagonal_matrix_compress_of_stack(
    int rows, TridiagonalMatrixBean (*uncompressed)[rows]) {
    
    if (uncompressed == NULL || rows < 0) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_ACCESS_ERROR);
        return NULL;
    }

    int compressed_bean_size = rows + (rows - 1) * 2;

    TridiagonalMatrixBean* compressed =
        (TridiagonalMatrixBean*) malloc (sizeof(TridiagonalMatrixBean) * compressed_bean_size);
    
    if (compressed == NULL) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_BEAN_INIT_ERROR);
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
tridiagonal_matrix_uncompress(int compressed_szie, TridiagonalMatrixBean* compressed) {

    if (compressed == NULL || compressed_szie < 0) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_ACCESS_ERROR);
        return NULL;
    }

    int rows = calculate_uncompressed_matrix_size(compressed_szie);

    TridiagonalMatrixBean** uncompressed = 
        (TridiagonalMatrixBean**) malloc (sizeof(TridiagonalMatrixBean*) * rows);

    if (uncompressed == NULL) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_BEAN_INIT_ERROR);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        uncompressed[i] = (TridiagonalMatrixBean*) malloc (sizeof(TridiagonalMatrixBean) * rows);

        if (uncompressed == NULL) {
            fprintf(stderr, TRIDIAGONAL_MATRIX_BEAN_INIT_ERROR);
            for (int j = 0; j < i; j++) {
                free(uncompressed[j]);
            }
            free(uncompressed);
            return NULL;
        }
    }

    int compressed_offset = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (abs(i -j) <= 1) {
                uncompressed[i][j] = compressed[compressed_offset++];
            } else {
                uncompressed[i][j] = 0;
            }
        }
    }

    return uncompressed;
}


int tridiagonal_matrix_compressed_bean_display(
    int compressed_size, TridiagonalMatrixBean* compressed) {
    
    if (compressed == NULL || compressed_size < 0) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_ACCESS_ERROR);
        return 0;
    }

    printf("TridiagonalMatrix: {  ");
    for (int i = 0; i < compressed_size; i++) {
        printf("%d  ", compressed[i]);
    }
    printf("}\n");
    return 0;
}


int
tridiagonal_matrix_uncompressed_bean_display(int rows, TridiagonalMatrixBean** uncompressed) {
    if (uncompressed ==NULL || *uncompressed ==NULL || rows < 0) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_ACCESS_ERROR);
        return -1;
    }

    printf("TridiagonalMatrix: {\n");
    for (int i = 0; i < rows; i++) {
        printf("    {  ");
        for (int j = 0; j < rows; j++) {
            printf("%d  ", uncompressed[i][j]);
        }
        printf("}\n");
    }
    printf("}\n");
    return 0;
}


int
tridiagonal_matrix_compressed_bean_clean(TridiagonalMatrixBean** compressed) {

    if (compressed == NULL || *compressed == NULL) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_ACCESS_ERROR);
        return 0;
    }

    free(*compressed);

    *compressed = NULL;

    return 0;
}


int
tridiagonal_matrix_uncompressed_bean_clean(int rows, TridiagonalMatrixBean*** uncompressed) {
    if (*uncompressed == NULL || *(*uncompressed) == NULL || rows < 0) {
        fprintf(stderr, TRIDIAGONAL_MATRIX_ACCESS_ERROR);
        return -1;
    }
    
    for (int i = 0; i < rows; i++) {
        free((*uncompressed)[i]);
    }
    free(*uncompressed);

    *uncompressed == NULL;

    return 0;
}
