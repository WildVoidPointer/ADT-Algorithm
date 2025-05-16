#include "sparse_matrix_compress.h"


int 
calculate_compressed_matrix_size(
    SparseMatrixEleType* fiducial, int rows, SparseMatrixEleType (*uncompressed)[rows]) {

    if (uncompressed == NULL || fiducial == NULL || rows < 0) {
        fprintf(stderr, SPARSE_MATRIX_ACCESS_ERROR);
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
        fprintf(stderr, SPARSE_MATRIX_ACCESS_ERROR);
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
        fprintf(stderr, SPARSE_MATRIX_ACCESS_ERROR);
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


int sparse_matrix_compressed_bean_display(SparseMatrixBean* commpressed) {

    if (commpressed == NULL) {
        fprintf(stderr, SPARSE_MATRIX_ACCESS_ERROR);
        return -1;
    }

    printf("SparseMatrix: {  ");
    for (int i = 0; i < commpressed->size; i++) {
        printf("%d  ", commpressed->units[i].data);
    }
    printf("}\n");
    return 0;
}
