#include "sparse_matrix_compress.h"


int 
calculate_compressed_matrix_size(
    SparseMatrixEleType* fiducial, int rows, SparseMatrixEleType (*uncompressed)[rows]) {

    if (uncompressed == NULL || fiducial == NULL || rows < 0) {
        fprintf(stderr, SPARSE_MATRIX_BEAN_ACCESS_ERROR);
        return -1;

    } else {
        int compressed_size = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < rows; j++) {
                if (uncompressed[i][j] != *fiducial) {
                    compressed_size++;
                }
            }
        }
        return compressed_size;
    }
}


SparseMatrixBean*
sparse_matrix_compress_of_stack(
    SparseMatrixEleType* fiducial, int rows, SparseMatrixEleType (*uncompressed)[rows]) {

    if (fiducial == NULL || uncompressed == NULL || rows < 0) {
        fprintf(stderr, SPARSE_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }

    SparseMatrixBean* compressed = 
        (SparseMatrixBean*) malloc (sizeof(SparseMatrixBean));

    if (compressed == NULL) {
        fprintf(stderr, SPARSE_MATRIX_BEAN_INIT_ERROR);
        return NULL;
    }

    int compressed_size = calculate_compressed_matrix_size(fiducial, rows, uncompressed);

    if (compressed_size == -1) {
        fprintf(stderr, SPARSE_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }

    compressed->units = (SparseMatrixUnit*) malloc (sizeof(SparseMatrixUnit) * compressed_size);

    if (compressed->units == NULL) {
        fprintf(stderr, SPARSE_MATRIX_UNIT_INIT_ERROR);
        free(compressed);
        return NULL;
    }

    compressed->rows = rows;

    compressed->size = compressed_size;

    int compressed_offset = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (uncompressed[i][j] != *fiducial) {
                compressed->units[compressed_offset].row = i;
                compressed->units[compressed_offset].col = j;
                compressed->units[compressed_offset++].data = uncompressed[i][j];
            }
        }
    }
    return compressed;
}


SparseMatrixEleType**
sparse_matrix_uncompress(SparseMatrixEleType* fiducial, SparseMatrixBean* compressed) {
    if (compressed == NULL || compressed->units == NULL || 
            compressed->rows < 0 || compressed->size < 0) {

        fprintf(stderr, SPARSE_MATRIX_BEAN_ACCESS_ERROR);
        return NULL;
    }

    SparseMatrixEleType** uncompressed = 
        (SparseMatrixEleType**) malloc (sizeof(SparseMatrixEleType*) * compressed->rows);
    
    if (uncompressed == NULL) {
        fprintf(stderr, SPARSE_MATRIX_BEAN_INIT_ERROR);
        return NULL;
    }

    for (int i = 0; i < compressed->rows; i++) {

        uncompressed[i] = 
            (SparseMatrixEleType*) malloc (sizeof(SparseMatrixEleType) * compressed->rows);

        if (uncompressed[i] == NULL) {
            fprintf(stderr, SPARSE_MATRIX_BEAN_INIT_ERROR);
            for (int j = 0; j < i; j++) {
                free(uncompressed[j]);
            }
            free(uncompressed);
        }
    }
    
    int compressed_offset = 0;

    for (int i = 0; i < compressed->rows; i++) {
        for (int j = 0; j < compressed->rows; j++) {
            uncompressed[i][j] = *fiducial;
        }
    }

    for (int i = 0; i < compressed->size; i++) {
        uncompressed[compressed->units[i].row][compressed->units[i].col] = 
            compressed->units[i].data;
    }

    return uncompressed;
}


int sparse_matrix_compressed_bean_display(SparseMatrixBean* compressed) {

    if (compressed == NULL) {
        fprintf(stderr, SPARSE_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    printf("SparseMatrix: {  ");
    for (int i = 0; i < compressed->size; i++) {
        printf("%d  ", compressed->units[i].data);
    }
    printf("}\n");
    return 0;
}


int sparse_matrix_uncompressed_bean_display(int rows, SparseMatrixEleType** uncompressed) {
    if (uncompressed == NULL || *uncompressed == NULL || rows < 0) {
        fprintf(stderr, SPARSE_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    printf("SparseMatrix: {\n");
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



int sparse_matrix_compressed_bean_clean(SparseMatrixBean** compressed) {
    if (compressed == NULL || *compressed == NULL) {
        fprintf(stderr, SPARSE_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    free((*compressed)->units);
    free(*compressed);
    *compressed = NULL;
    return 0;
}


int sparse_matrix_uncompressed_bean_clean(
    int rows, SparseMatrixEleType*** uncompressed) {
    
    if (uncompressed == NULL || *uncompressed == NULL || rows < 0) {
        fprintf(stderr, SPARSE_MATRIX_BEAN_ACCESS_ERROR);
        return -1;
    }

    for (int i = 0; i < rows; i++) {
        free((*uncompressed)[i]);
    }

    free(*uncompressed);
    *uncompressed = NULL;
    return 0;
}
