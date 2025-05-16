#ifndef TRIDIAGONAL_MATRIX_COMPRESS_H
#define TRIDIAGONAL_MATRIX_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>


#define TRIDIAGONAL_MATRIX_ACCESS_ERROR \
    "TridiagonalMatrixAccessError: The data address of thecTridiagonalMatrixBean cannot be accessed\n"

#define TRIDIAGONAL_MATRIX_BEAN_INIT_ERROR \
    "TridiagonalMatrixBeanInitError: Memory initialization of TridiagonalMatrixBean failed\n"


typedef int TridiagonalMatrixBean;


TridiagonalMatrixBean*
tridiagonal_matrix_compress_of_heap(int rows, TridiagonalMatrixBean** uncompressed);

TridiagonalMatrixBean*
tridiagonal_matrix_compress_of_stack(int rows, TridiagonalMatrixBean (*uncompressed)[rows]);

TridiagonalMatrixBean**
tridiagonal_matrix_uncompress(int compressed_szie, TridiagonalMatrixBean* compressed);

int calculate_uncompressed_matrix_size(int compressed_size);

int tridiagonal_matrix_compressed_bean_display(
    int compressed_size, TridiagonalMatrixBean* compressed);

int tridiagonal_matrix_uncompressed_bean_display(
    int rows, TridiagonalMatrixBean** uncompressed);

int
tridiagonal_matrix_compressed_bean_clean(TridiagonalMatrixBean** compressed);

int
tridiagonal_matrix_uncompressed_bean_clean(int rows, TridiagonalMatrixBean*** uncompressed);

#endif