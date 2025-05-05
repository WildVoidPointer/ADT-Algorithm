#ifndef SYMMETRIC_MATRIX_COMPRESS_H
#define SYMMETRIC_MATRIX_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define SYMMETRIC_MATRIX_BEAN_INIT_ERROR \
    "SymmetricMatrixInitError: Failed to allocate memory for SymmetricMatrixCompressBean\n"

#define SYMMETRIC_MATRIX_BEAN_ACCESS_ERROR \
    "SymmetricMatrixBeanAccessError: Failed to access the SymmetricMatrixBean\n"


typedef int SymmetricMatrixCompressBean;


SymmetricMatrixCompressBean* symmetric_matrix_compress(
    int rows, SymmetricMatrixCompressBean (*uncompressed)[]);


int calculate_uncompressed_matrix_size(int compressed_size);

SymmetricMatrixCompressBean* symmetric_matrix_uncompress(
    SymmetricMatrixCompressBean* compressed, int compressed_size);

SymmetricMatrixCompressBean* symmetric_matrix_flat_uncompress(
    SymmetricMatrixCompressBean* compressed, int compressed_size);

int symmetric_matrix_flat_display(
    SymmetricMatrixCompressBean* flat_matrix, int raws);

int symmetric_matrix_uncompressed_bean_clean(
    SymmetricMatrixCompressBean*** bean, int size);

int symmetric_matrix_compress_bean_clean(SymmetricMatrixCompressBean** bean);

#endif