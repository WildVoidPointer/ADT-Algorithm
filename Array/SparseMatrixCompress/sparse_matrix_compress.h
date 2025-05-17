#ifndef SPARSE_MATRIX_COMPRESS_H
#define SPARSE_MATRIX_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>


#define SPARSE_MATRIX_BEAN_ACCESS_ERROR \
    "SparseMatrixAccessError: The data address of the SparseMatrixBean cannot be accessed\n"

#define SPARSE_MATRIX_BEAN_INIT_ERROR \
    "SparseMatrixBeanInitError: Memory initialization of SparseMatrixBean failed\n"

#define SPARSE_MATRIX_UNIT_INIT_ERROR \
    "SparseMatrixUnitInitError: Memory initialization of SparseMatrixUnit failed\n"


typedef int SparseMatrixEleType;


typedef struct SparseMatrixUnit {
    int row;
    int col;
    SparseMatrixEleType data;
} SparseMatrixUnit;


typedef struct {
    SparseMatrixUnit* units;
    int rows;
    int size;
} SparseMatrixBean;


int calculate_compressed_matrix_size(
    SparseMatrixEleType* fiducial, int rows, SparseMatrixEleType (*uncompressed)[rows]);

SparseMatrixBean*
sparse_matrix_compress_of_stack(
    SparseMatrixEleType* fiducial, int rows, SparseMatrixEleType (*uncompressed)[rows]);

SparseMatrixEleType**
sparse_matrix_uncompress(SparseMatrixEleType* fiducial, SparseMatrixBean* compressed);

int sparse_matrix_compressed_bean_display(SparseMatrixBean* commpressed);

int sparse_matrix_uncompressed_bean_display(int rows, SparseMatrixEleType** uncompressed);

int sparse_matrix_compressed_bean_clean(SparseMatrixBean** compressed);

int sparse_matrix_uncompressed_bean_clean(int rows, SparseMatrixEleType*** uncompressed);

#endif
