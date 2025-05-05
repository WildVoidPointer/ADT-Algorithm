#include "symmetricmatrixcompress.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



SymmetricMatrixBean* 
symmetric_matrix_compress(
    int rows, SymmetricMatrixBean (*uncompressed)[rows]) {
        
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


SymmetricMatrixBean*
symmetric_matrix_uncompress(
    SymmetricMatrixBean* compressed, int compressed_size) {

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
}


SymmetricMatrixBean*
symmetric_matrix_flat_uncompress(
    SymmetricMatrixBean* compressed, int compressed_size) {

    int rows = calculate_uncompressed_matrix_size(compressed_size);
    if (rows == -1) {
        return NULL;
    }

    SymmetricMatrixBean* uncompressed = 
        (SymmetricMatrixBean*) malloc 
        (sizeof(SymmetricMatrixBean) * rows * rows);

    if (uncompressed == NULL) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_INIT_ERROR);

        return NULL;
    }

    int compress_offset = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            uncompressed[i * rows + j] 
                = uncompressed[j * rows + i] 
                = compressed[compress_offset++];
        }
    }
    return uncompressed;
}


int
symmetric_matrix_flat_display(
    SymmetricMatrixBean* flat_matrix, int raws) {

    if (flat_matrix == NULL) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    printf("SymmetricMatrix:  {\n");
    for (int i = 0; i < raws; i++) {
        printf("    { ");
        for (int j = 0; j < raws; j++) {
            printf("%d ", flat_matrix[i * raws + j]);
        }
        printf("}\n");
    }
    printf("}\n");
    return 0;
}


int symmetric_matrix_uncompressed_bean_clean(
    SymmetricMatrixBean*** bean, int size) {
    
    if (bean == NULL || *bean == NULL) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    for (int i = 0; i < size; i++) {
        free(*bean[i]);
    }

    free(*bean);
    *bean = NULL;
    return 0;
}


int symmetric_matrix_flat_bean_clean(SymmetricMatrixBean** bean) {
    if (bean == NULL || *bean == NULL) {
        fprintf(stderr, SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }
    free(*bean);
    *bean = NULL;
    return 0;
}

