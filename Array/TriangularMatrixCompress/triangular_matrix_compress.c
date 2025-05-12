#include "triangular_matrix_compress.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int calculate_uncompressed_matrix_size(int compressed_size) {
    return (compressed_size >= 0) ? 
        ((int)sqrt(1 + (compressed_size - 1) * 8) - 1) / 2 : -1;
}


TriangularMatrixBean*
lower_triangular_matrix_compress(int rows, TriangularMatrixBean (*uncompressed)[rows]) {
    if (uncompressed == NULL || rows < 0) {
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


TriangularMatrixBean**
lower_triangular_matrix_uncompress(int compressed_size, TriangularMatrixBean* compressed) {
    if (compressed == NULL || compressed_size < 0) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }

    int rows = calculate_uncompressed_matrix_size(compressed_size);

    TriangularMatrixBean** uncompressed = 
        (TriangularMatrixBean**) malloc (sizeof(TriangularMatrixBean*) * rows);
    
    if (uncompressed == NULL) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        uncompressed[i] = (TriangularMatrixBean*) malloc (sizeof(TriangularMatrixBean) * rows);
        if (uncompressed[i] == NULL) {
            fprintf(stderr, TRIANGULAR_MATRIX_BEAN_INIT_ERROR);
            for (int j = 0; j < i; j++) {
                free(uncompressed[j]);
            }
            free(uncompressed);
            return NULL;
        }
    }

    TriangularMatrixBean upper_element = compressed[compressed_size - 1];
    int compressed_offset = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            uncompressed[i][j] = compressed[compressed_offset++];
        }

        for (int j = i + 1; j < rows; j++) {
            uncompressed[i][j] = upper_element;
        }
        
    }
    return uncompressed;
}



TriangularMatrixBean*
upper_triangular_matrix_compress(int rows, TriangularMatrixBean (*uncompressed)[rows]) {
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
        for (int j = i; j < rows; j++) {
            compressed[compressed_offset++] = uncompressed[i][j];
        }
    }
    compressed[compressed_offset] = uncompressed[rows - 1][0];
    return compressed;
}


TriangularMatrixBean**
upper_triangular_matrix_uncompressed(int compressed_size, TriangularMatrixBean* compressed) {
    if (compressed == NULL || compressed_size < 0) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }

    int rows = calculate_uncompressed_matrix_size(compressed_size);

    TriangularMatrixBean** uncompressed = 
        (TriangularMatrixBean**) malloc (sizeof(TriangularMatrixBean*) * rows);
    
    if (uncompressed == NULL) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        uncompressed[i] = (TriangularMatrixBean*) malloc (sizeof(TriangularMatrixBean) * rows);
        if (uncompressed[i] == NULL) {
            fprintf(stderr, TRIANGULAR_MATRIX_BEAN_INIT_ERROR);
            for (int j = 0; j < i; j++) {
                free(uncompressed[j]);
            }
            free(uncompressed);
            return NULL;
        }
    }

    TriangularMatrixBean lower_element = compressed[compressed_size - 1];
    int compressed_offset = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < i; j++) {
            uncompressed[i][j] = lower_element;
        }
        for (int j = i; j < rows; j++) {
            uncompressed[i][j] = compressed[compressed_offset++];
        }
    }

    return uncompressed;
}


int 
triangular_matrix_uncompressed_bean_display(int rows, TriangularMatrixBean** uncompressed) {
    if (uncompressed == NULL || *uncompressed == NULL || rows < 0) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    printf("TriangularMatrix: {\n");
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
triangular_matrix_compressed_bean_display(int compressed_size, TriangularMatrixBean* compressed){
    if (compressed == NULL) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }
    printf("TriangularMatrix: {  ");
    for (int i = 0; i < compressed_size; i++) {
        printf("%d  ", compressed[i]);
    }
    printf("}\n");
}


int
triangular_matrix_uncompressed_bean_clean(int rows, TriangularMatrixBean*** uncompressed) {
    if (*uncompressed == NULL || (*uncompressed) == NULL || rows < 0) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    for (int i = 0; i < rows; i++) {
        free((*uncompressed)[i]);
    }

    free(*uncompressed);
    *uncompressed = NULL;
    return 0;
}


int 
triangular_matrix_compressed_bean_clean(TriangularMatrixBean** compressed) {
    if (compressed == NULL || *compressed == NULL) {
        fprintf(stderr, TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    free(*compressed);
    *compressed = NULL;
    return 0;
}
