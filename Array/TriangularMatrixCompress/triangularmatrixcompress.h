#ifndef TRIANGULAR_MATRIX_COMPRESS_H
#define TRIANGULAR_MATRIX_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define TRIANGULAR_MATRIX_BEAN_INIT_ERROR \
    "TriangularMatrixBeanInitError: Failed to allocate memory for TriangularMatrixBean\n"

#define TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR \
    "TriangularMatrixBeanAccessError: Failed to access the TriangularMatrixBean\n"


typedef int TriangularMatrixBean;


int calculate_uncompressed_matrix_size(int compressed_size);

TriangularMatrixBean*
    lower_triangular_matrix_compress(int rows, TriangularMatrixBean (*uncompressed)[rows]);

TriangularMatrixBean**
    lower_triangular_matrix_uncompress(int compressed_size, TriangularMatrixBean* compressed);

TriangularMatrixBean*
    upper_triangular_matrix_compress(int rows, TriangularMatrixBean (*uncompressed)[rows]);

TriangularMatrixBean**
    upper_triangular_matrix_uncompressed(int copressed_size, TriangularMatrixBean* compressed);

int triangular_matrix_uncompressed_bean_display(int rows, TriangularMatrixBean** uncompressed);

int triangular_matrix_compressed_bean_display(int compressed_size, TriangularMatrixBean* uncompressed);

int triangular_matrix_uncompressed_bean_clean(int rows, TriangularMatrixBean*** uncompressed);

int triangular_matrix_compressed_bean_clean(TriangularMatrixBean** compressed);

#endif
