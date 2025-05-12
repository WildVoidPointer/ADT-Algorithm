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


int calculate_uncompressed_matrix_size(int compressed_size);

SymmetricMatrixBean* symmetric_matrix_compress(
    int rows, SymmetricMatrixBean (*uncompressed)[rows]);

SymmetricMatrixBean** symmetric_matrix_uncompress(
    int compressed_size, SymmetricMatrixBean* compressed);

int symmetric_matrix_uncompressed_bean_display(
    int rows, SymmetricMatrixBean** uncompressed);

int symmetric_matrix_compressed_bean_display(
    int compressed_size, SymmetricMatrixBean* compressed);

int symmetric_matrix_uncompressed_bean_clean(
    int rows, SymmetricMatrixBean*** uncompressed);

int symmetric_matrix_compressed_bean_clean(SymmetricMatrixBean** compressed);

#endif