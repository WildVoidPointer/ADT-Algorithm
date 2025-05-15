#ifndef TRIDIAGONAL_MATRIX_COMPRESS_H
#define TRIDIAGONAL_MATRIX_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>


#define TRIDIAGNAOL_MATRIX_ACCESS_ERROR \
    "TridiagonalMatrixAccessError: The data address of the triangular matrix cannot be accessed\n"

#define TRIDIAGNAOL_MATRIX_BEAN_INIT_ERROR \
    "TridiagonalMatrixBeanInitError: Memory initialization of TridiagonalMatrixBean failed\n"


typedef int TridiagonalMatrixBean;


TridiagonalMatrixBean*
tridiagonal_matrix_compress();

TridiagonalMatrixBean*
tridiagnaol_matrix_compress_of_stack(int rows, TridiagonalMatrixBean (*uncompressed)[rows]);

TridiagonalMatrixBean**
tridiagnaol_matrix_uncompress(int compressed_szie, TridiagonalMatrixBean* compressed);

int calculate_uncompressed_matrix_size(int compressed_size);

int tridiagnaol_matrix_compressed_bean_display(
    int compressed_size, TridiagonalMatrixBean* compressed);

int tridiagnaol_matrix_uncompressed_bean_display(
    int rows, TridiagonalMatrixBean** uncompressed);

int
tridiagnaol_matrix_compressed_bean_clean(TridiagonalMatrixBean** compressed);

#endif