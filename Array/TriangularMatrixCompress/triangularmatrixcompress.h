#ifndef TRIANGULAR_MATRIX_COMPRESS_H
#define TRIANGULAR_MATRIX_COMPRESS_H

#include <stdio.h>
#include <stdlib.h>


#define TRIANGULAR_MATRIX_BEAN_INIT_ERROR \
    "TriangularMatrixBeanInitError: Failed to allocate memory for TriangularMatrixBean\n"

#define TRIANGULAR_MATRIX_BEAN_ACCESS_ERROR \
    "TriangularMatrixBeanAccessError: Failed to access the TriangularMatrixBean\n"


typedef int TriangularMatrixBean;


TriangularMatrixBean*
    lower_triangular_matrix_compress(int rows, TriangularMatrixBean (*uncompressed)[rows]);

int triangular_matrix_flat_bean_clean(TriangularMatrixBean** compressed);

#endif