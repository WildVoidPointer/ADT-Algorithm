#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define MATRIX_CREATE_ERROR \
    "MatrixCreateError: Memory initialization of Matrix failed\n"

#define MATRIX_INIT_ERROR \
    "MatrixInitError: The initialization data address cannot be loaded\n"

#define MATRIX_ACCESS_EXCEPTION \
    "MatrixAccessException: The Matrix cannot be accessed\n"

#define MATRIX_COMPRESS_OPTIONS_ERROR \
    "MatrixCompressOptionsError: The compressed or uncompressed space cannot be allocated\n"

#define COMPRESSED_MATRIX_CREATE_ERROR \
    "CompressedMatrixCreateError: Memory initialization of CompressedMatrix failed\n"

#define COMPRESSED_MATRIX_ACCESS_EXCEPTION \
    "CompressedMatrixAccessException: The CompressedMatrix cannot be accessed\n"


typedef enum MatrixInitModeEnum {
    MATRIX_INIT_DISABLE,
    MATRIX_INIT_ENABLE
} MatrixInitModeEnum;


typedef int MatrixEleType;


typedef struct Matrix {
    MatrixEleType* data;
    MatrixEleType init_data;
    size_t rows;
    size_t cols;
    int is_init;
} Matrix;


typedef struct CompressedMatrix {
    MatrixEleType* data;
    size_t compressed_size;
} CompressedMatrix;


Matrix* Matrix_create(size_t rows, size_t cols, 
    MatrixInitModeEnum is_init, MatrixEleType* init_data);

Matrix* Matrix_build_of_stack(
    size_t rows, size_t cols, MatrixEleType (*stack_matrix)[cols]);

int Matrix_clean(Matrix** matrix);

int Matrix_display(Matrix* matrix);


size_t Matrix_calculate_tridiagonal_compress_size(Matrix* matrix);

size_t Matrix_calculate_tridiagonal_uncompress_size(CompressedMatrix* compressed);

CompressedMatrix* Matrix_compress_tridiagonal_matrix(Matrix* matrix);

Matrix* Matrix_uncompress_tridiagonal_matrix(
    CompressedMatrix* compressed, MatrixEleType* filler);


size_t Matrix_calculate_symmetric_compress_size(Matrix* matrix);

size_t Matrix_calculate_symmetric_uncompress_size(CompressedMatrix* compressed);

CompressedMatrix* Matrix_compress_symmetric_matrix(Matrix* matrix);

Matrix* Matrix_uncompress_symmetric_matrix(
    CompressedMatrix* compressed, MatrixEleType* filler);


CompressedMatrix* CompressedMatrix_create(size_t compressed_size);

int CompressedMatrix_clean(CompressedMatrix** compressed);

int CompressedMatrix_display(CompressedMatrix* compressed);






// TridiagonalMatrixBean*
// tridiagonal_matrix_compress_of_heap(int rows, TridiagonalMatrixBean** uncompressed);

// TridiagonalMatrixBean*
// tridiagonal_matrix_compress_of_stack(int rows, TridiagonalMatrixBean (*uncompressed)[rows]);

// TridiagonalMatrixBean**
// tridiagonal_matrix_uncompress(int compressed_szie, TridiagonalMatrixBean* compressed);

// int calculate_uncompressed_matrix_size(int compressed_size);

// int tridiagonal_matrix_compressed_bean_display(
//     int compressed_size, TridiagonalMatrixBean* compressed);

// int tridiagonal_matrix_uncompressed_bean_display(
//     int rows, TridiagonalMatrixBean** uncompressed);

// int
// tridiagonal_matrix_compressed_bean_clean(TridiagonalMatrixBean** compressed);

// int
// tridiagonal_matrix_uncompressed_bean_clean(int rows, TridiagonalMatrixBean*** uncompressed);

#endif