#ifndef SYMMETRIC_MATRIX_COMPRESS_H
#define SYMMETRIC_MATRIX_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define SYMMETRIC_MATRIX_BEAN_INIT_ERROR \
    "SymmetricMatrixBeanInitError: Failed to allocate memory for SymmetricMatrixBean\n"

#define SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR \
    "SymmetricMatrixBeanAccessError: Failed to access the SymmetricMatrixBean\n"


typedef int SymmetricMatrixBean;


SymmetricMatrixBean* symmetric_matrix_compress(
    int rows, SymmetricMatrixBean (*uncompressed)[rows]);

int calculate_uncompressed_matrix_size(int compressed_size);

SymmetricMatrixBean* symmetric_matrix_uncompress(
    SymmetricMatrixBean* compressed, int compressed_size);

SymmetricMatrixBean* symmetric_matrix_flat_uncompress(
    SymmetricMatrixBean* compressed, int compressed_size);

int symmetric_matrix_flat_display(
    SymmetricMatrixBean* flat_matrix, int raws);

int symmetric_matrix_uncompressed_bean_clean(
    SymmetricMatrixBean*** bean, int size);

int symmetric_matrix_flat_bean_clean(SymmetricMatrixBean** bean);

#endif