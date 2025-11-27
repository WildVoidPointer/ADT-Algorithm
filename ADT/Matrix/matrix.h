#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __linux__
    #include <sys/types.h>
#endif


#define MATRIX_CREATE_ERROR \
    "MatrixCreateError: " \
    "Memory initialization of Matrix failed\n"


#define MATRIX_COPY_ERROR \
    "MatrixCopyError: " \
    "Memory initialization of Matrix failed\n"


#define MATRIX_INIT_ERROR \
    "MatrixInitError: " \
    "The initialization data address cannot be loaded\n"


#define MATRIX_OPERATION_ERROR \
    "MatrixOperationError: " \
    "Memory initialization of Matrix failed\n"


#define MATRIX_ACCESS_EXCEPTION \
    "MatrixAccessException: The Matrix cannot be accessed\n"


#define MATRIX_OPERATION_EXCEPTION \
    "MatrixOperationException:" \
    "The matrix does not meet the operation conditions\n"


#define MATRIX_COMPRESS_OPTIONS_ERROR \
    "MatrixCompressOptionsError: " \
    "The compressed or uncompressed space cannot be allocated\n"


#define COMPRESSED_MATRIX_CREATE_ERROR \
    "CompressedMatrixCreateError: " \
    "Memory initialization of CompressedMatrix failed\n"

#define COMPRESSED_MATRIX_ACCESS_EXCEPTION \
    "CompressedMatrixAccessException: " \
    "The CompressedMatrix cannot be accessed\n"


#define COMPRESSED_SPARSE_MATRIX_CREATE_ERROR \
    "CompressedSparseMatrixCreateError: " \
    "Memory initialization of CompressedSparseMatrix failed\n"

#define COMPRESSED_SPARSE_MATRIX_ACCESS_EXCEPTION \
    "CompressedSparseMatrixAccessException: " \
    "The CompressedSparseMatrix cannot be accessed\n"


typedef enum MatrixInitModeEnum {
    MATRIX_INIT_DISABLE,
    MATRIX_INIT_ENABLE
} MatrixInitModeEnum;


typedef int MatrixDataType;


typedef struct Matrix {
    MatrixDataType* data;
    MatrixDataType init_data;
    size_t rows;
    size_t cols;
    int is_init;
} Matrix;


typedef struct CompressedMatrix {
    MatrixDataType* data;
    size_t compressed_size;
} CompressedMatrix;


typedef struct CompressedSparseMatrixUnit {
    size_t row;
    size_t col;
    MatrixDataType data;
} CompressedSparseMatrixUnit;


typedef struct CompressedSparseMatrix {
    CompressedSparseMatrixUnit* units;
    size_t compressed_size;
    size_t rows;
    size_t cols;
} CompressedSparseMatrix;


Matrix* Matrix_create(
    size_t rows, size_t cols, 
    MatrixInitModeEnum is_init, MatrixDataType* init_data
);


Matrix* Matrix_copy(Matrix* matrix);


int Matrix_add(Matrix* m1, Matrix* m2);


int Matrix_subtract(Matrix* m1, Matrix* m2);


Matrix* Matrix_multiply(Matrix* m1, Matrix* m2);


int Matrix_set_element(
    Matrix* matrix, size_t row, size_t col, 
    MatrixDataType* data
);


Matrix* Matrix_build_of_array(
    size_t rows, size_t cols, 
    MatrixDataType (*stack_matrix)[cols]
);


MatrixDataType* _Matrix_get_element_unsafe(
    Matrix* matrix, size_t rows, size_t cols
);


int Matrix_destroy(Matrix** matrix);


int Matrix_display(Matrix* matrix);


size_t 
Matrix_calculate_tridiagonal_compress_size(Matrix* matrix);


size_t Matrix_calculate_tridiagonal_uncompress_size(
    CompressedMatrix* compressed
);


CompressedMatrix* 
Matrix_compress_tridiagonal_matrix(Matrix* matrix);


Matrix* Matrix_uncompress_tridiagonal_matrix(
    CompressedMatrix* compressed, MatrixDataType* filler
);


size_t Matrix_calculate_symmetric_compress_size(Matrix* matrix);


size_t Matrix_calculate_symmetric_uncompress_size(
    CompressedMatrix* compressed
);


CompressedMatrix* 
Matrix_compress_symmetric_matrix(Matrix* matrix);


Matrix* Matrix_uncompress_symmetric_matrix(
    CompressedMatrix* compressed, MatrixDataType* filler
);


size_t Matrix_calculate_triangular_compress_size(Matrix* matrix);


size_t Matrix_calculate_triangular_uncompress_size(
    CompressedMatrix* compressed
);


CompressedMatrix* 
Matrix_compress_lower_triangular_matrix(Matrix* matrix);


CompressedMatrix* 
Matrix_compress_upper_triangular_matrix(Matrix* matrix);


Matrix* Matrix_uncompress_lower_triangular_matrix(
    CompressedMatrix* compressed, 
    MatrixDataType* filler
);


Matrix* Matrix_uncompress_upper_triangular_matrix(
    CompressedMatrix* compressed, 
    MatrixDataType* filler
);


size_t Matrix_calculate_sparse_compress_size(
    Matrix* matrix, MatrixDataType* fiducial
);


CompressedSparseMatrix*Matrix_compress_sparse_matrix(
    Matrix* matrix, MatrixDataType* fiducial
);


Matrix* Matrix_uncompress_sparse_matrix(
    CompressedSparseMatrix* compressed, MatrixDataType* fiducial
);


CompressedMatrix* 
CompressedMatrix_create(size_t compressed_size);


int CompressedMatrix_destroy(CompressedMatrix** compressed);


int CompressedMatrix_display(CompressedMatrix* compressed);


CompressedSparseMatrix* CompressedSparseMatrix_create(
    Matrix* matrix, size_t compressed_size
);


int CompressedSparseMatrix_destroy(
    CompressedSparseMatrix** compressed
);


int CompressedSparseMatrix_display(
    CompressedSparseMatrix* compressed
);


#endif
