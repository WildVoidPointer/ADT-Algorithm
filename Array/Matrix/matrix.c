#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"


Matrix* 
Matrix_create(size_t rows, size_t cols, MatrixInitModeEnum is_init, MatrixEleType* init_data) {

    Matrix* matrix = (Matrix*) malloc (sizeof(Matrix));
    if (matrix == NULL) {
        fprintf(stderr, MATRIX_CREATE_ERROR);
        return NULL;
    }

    matrix->data = 
        (MatrixEleType*) malloc (sizeof(MatrixEleType) * rows * cols);
    if (matrix->data == NULL) {
        fprintf(stderr, MATRIX_CREATE_ERROR);
        free(matrix);
        return NULL;
    }

    if (is_init == (MatrixInitModeEnum) MATRIX_INIT_ENABLE) {
        if (init_data == NULL) {
            fprintf(stderr, MATRIX_INIT_ERROR);
            return matrix;
        }
        matrix->is_init = 1;
        matrix->init_data = *init_data;
        for (size_t i = 0; i < cols * rows; i++) {
            matrix->data[i] = *init_data;
        }
    } else {
        matrix->is_init = 0;
    }

    matrix->rows = rows;
    matrix->cols = cols;
    return matrix;
}


Matrix* 
Matrix_build_of_stack(size_t rows, size_t cols, MatrixEleType (*stack_matrix)[cols]) {

    Matrix* matrix = 
        Matrix_create(rows, cols, MATRIX_INIT_DISABLE, NULL);

    if (matrix == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix->data[i * cols + j] = stack_matrix[i][j];
        }
    }

    return matrix;
}


MatrixEleType* 
_Matrix_get_element_address(Matrix* matrix, size_t rows, size_t cols) {
    if (matrix == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return NULL;
    }

    return &(matrix->data[rows * matrix->cols + cols]);
}


int Matrix_clean(Matrix** matrix) {
    if (matrix == NULL || *matrix == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return -1;
    }
    
    free((*matrix)->data);
    
    free(*matrix);
    *matrix = NULL;
    
    return 0;
}


int Matrix_display(Matrix* matrix) {
    if (matrix == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return -1;
    }

    fprintf(stdout, "Matrix: {\n");
    for(size_t i = 0; i < matrix->rows; i++) {
        printf("    {  ");
        for (size_t j = 0; j < matrix->cols; j++) {
            printf("%d  ", *(_Matrix_get_element_address(matrix, i, j)));
        }
        printf("}\n");
    }
    printf("}\n");
}


size_t Matrix_calculate_tridiagonal_compress_size(Matrix* matrix) {
    if (matrix == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return 0;
    }

    return matrix->rows + (matrix->rows - 1) * 2;
}


size_t 
Matrix_calculate_tridiagonal_uncompress_size(CompressedMatrix* compressed) {
    if (compressed == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_ACCESS_EXCEPTION);
        return 0;
    }

    return (compressed->compressed_size + 2) / 3;
}


CompressedMatrix* 
Matrix_compress_tridiagonal_matrix(Matrix* matrix) {

    if (matrix == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return NULL;
    }

    size_t compressed_size = 
        Matrix_calculate_tridiagonal_compress_size(matrix);

    CompressedMatrix* compressed =
        CompressedMatrix_create(compressed_size);
    
    if (compressed == NULL) {
        fprintf(stderr, MATRIX_COMPRESS_OPTIONS_ERROR);
        return NULL;
    }
    
    size_t compressed_offset = 0;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            if (abs(i - j) <= 1) {
                compressed->data[compressed_offset++] =
                        *(_Matrix_get_element_address(matrix, i, j));
            }
        }
    }

    return compressed;
}


Matrix* 
Matrix_uncompress_tridiagonal_matrix(CompressedMatrix* compressed, MatrixEleType* filler) {

    if (compressed == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_ACCESS_EXCEPTION);
        return NULL;
    }

    size_t steps = Matrix_calculate_tridiagonal_uncompress_size(compressed);

    Matrix* matrix = Matrix_create(steps, steps, MATRIX_INIT_DISABLE, NULL);

    if (matrix == NULL) {
        fprintf(stderr, MATRIX_COMPRESS_OPTIONS_ERROR);
        return  NULL;
    }

    size_t compressed_offset = 0;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            if (abs(i -j) <= 1) {
                *(_Matrix_get_element_address(matrix, i, j)) = compressed->data[compressed_offset++];
            } else {
                *(_Matrix_get_element_address(matrix, i, j)) = *filler;
            }
        }
    }

    return matrix;
}


size_t Matrix_calculate_symmetric_compress_size(Matrix* matrix) {
    if (matrix == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return 0;
    }

    return (matrix->rows + 1) * matrix->rows / 2;
}


size_t Matrix_calculate_symmetric_uncompress_size(CompressedMatrix* compressed) {
    if (compressed == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_ACCESS_EXCEPTION);
        return 0;
    }

    return ((int)sqrt(1 + compressed->compressed_size * 8) - 1) / 2;
}


CompressedMatrix* Matrix_compress_symmetric_matrix(Matrix* matrix){
    if (matrix == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return NULL;
    }

    size_t compressed_size =
        Matrix_calculate_symmetric_compress_size(matrix);

    CompressedMatrix* compressed = 
        CompressedMatrix_create(compressed_size);

    if (compressed == NULL) {
        fprintf(stderr, MATRIX_COMPRESS_OPTIONS_ERROR);
        return NULL;
    }
    
    size_t compressed_offset = 0;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j <= i; j++) {
            compressed->data[compressed_offset++] = 
                *(_Matrix_get_element_address(matrix, i, j));
        }
    }

    return compressed;
}


Matrix* 
Matrix_uncompress_symmetric_matrix(CompressedMatrix* compressed, MatrixEleType* filler) {
    
    if (compressed == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_ACCESS_EXCEPTION);
        return NULL;
    }

    size_t steps = Matrix_calculate_symmetric_uncompress_size(compressed);

    Matrix* matrix = Matrix_create(steps, steps, MATRIX_INIT_DISABLE, NULL);

    if (matrix == NULL) {
        fprintf(stderr, MATRIX_COMPRESS_OPTIONS_ERROR);
        return  NULL;
    }

    size_t compressed_offset = 0;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j <= i; j++) {
            *(_Matrix_get_element_address(matrix, i, j)) = 
                *(_Matrix_get_element_address(matrix, j, i)) =
                compressed->data[compressed_offset++];
        }
    }

    return matrix;
}


size_t Matrix_calculate_triangular_compress_size(Matrix* matrix) {
    return Matrix_calculate_symmetric_compress_size(matrix);
}


size_t Matrix_calculate_triangular_uncompress_size(CompressedMatrix* compressed) {
    return Matrix_calculate_symmetric_uncompress_size(compressed);
}


CompressedMatrix* Matrix_compress_lower_triangular_matrix(Matrix* matrix) {
    return Matrix_compress_symmetric_matrix(matrix);
}


CompressedMatrix* Matrix_compress_upper_triangular_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return NULL;
    }

    size_t compressed_size =
        Matrix_calculate_triangular_compress_size(matrix);

    CompressedMatrix* compressed = 
        CompressedMatrix_create(compressed_size);

    if (compressed == NULL) {
        fprintf(stderr, MATRIX_COMPRESS_OPTIONS_ERROR);
        return NULL;
    }

    size_t compressed_offset = 0;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = i; j < matrix->cols; j++) {
            compressed->data[compressed_offset++] = 
                *(_Matrix_get_element_address(matrix, i, j));
        }
    }

    return compressed;
}


Matrix*
Matrix_uncompress_lower_triangular_matrix(CompressedMatrix* compressed, MatrixEleType* filler) {

    if (compressed == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_ACCESS_EXCEPTION);
        return NULL;
    }

    size_t steps = Matrix_calculate_triangular_uncompress_size(compressed);

    Matrix* matrix = Matrix_create(steps, steps, MATRIX_INIT_DISABLE, NULL);

    if (matrix == NULL) {
        fprintf(stderr, MATRIX_COMPRESS_OPTIONS_ERROR);
        return  NULL;
    }

    size_t compressed_offset = 0;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j <= i; j++) {
            *(_Matrix_get_element_address(matrix, i, j)) = 
                compressed->data[compressed_offset++];
        }

        for (size_t j = i + 1; j < matrix->cols; j++) {
            *(_Matrix_get_element_address(matrix, i, j)) = *filler;
        }
    }

    return matrix;
}


Matrix* 
Matrix_uncompress_upper_triangular_matrix(CompressedMatrix* compressed, MatrixEleType* filler) {
    if (compressed == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_ACCESS_EXCEPTION);
        return NULL;
    }

    size_t steps = Matrix_calculate_triangular_uncompress_size(compressed);

    Matrix* matrix = Matrix_create(steps, steps, MATRIX_INIT_DISABLE, NULL);

    if (matrix == NULL) {
        fprintf(stderr, MATRIX_COMPRESS_OPTIONS_ERROR);
        return  NULL;
    }

    size_t compressed_offset = 0;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j <= i; j++) {
            *(_Matrix_get_element_address(matrix, i, j)) = *filler;
        }

        for (size_t j = i; j < matrix->cols; j++) {
            *(_Matrix_get_element_address(matrix, i, j)) = 
                compressed->data[compressed_offset++];
        }
    }

    return matrix;
}


size_t Matrix_calculate_sparse_compress_size(Matrix* matrix, MatrixEleType* fiducial) {

    if (matrix == NULL || fiducial == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return  0;
    }

    size_t compressed_size = 0;

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            if (*(_Matrix_get_element_address(matrix, i, j)) != *fiducial) {
                compressed_size++;
            }
        }
    }

    return compressed_size;
}


CompressedSparseMatrix*
Matrix_compress_sparse_matrix(Matrix* matrix, MatrixEleType* fiducial) {

    if (matrix == NULL || fiducial == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return  NULL;
    }

    size_t compressed_size = Matrix_calculate_sparse_compress_size(matrix, fiducial);

    CompressedSparseMatrix* compressed = CompressedSparseMatrix_create(matrix, compressed_size);

    if (compressed == NULL) {
        fprintf(stderr, MATRIX_COMPRESS_OPTIONS_ERROR);
        return NULL;
    }

    size_t compressed_offset = 0;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            MatrixEleType* current = _Matrix_get_element_address(matrix, i, j);
            if (*current != *fiducial) {
                compressed->units[compressed_offset].data = *current;
                compressed->units[compressed_offset].row = i;
                compressed->units[compressed_offset++].col = j;
            }
        }
    }

    return compressed;
}


Matrix* Matrix_uncompress_sparse_matrix(CompressedSparseMatrix* compressed, MatrixEleType* fiducial) {

    if (compressed == NULL || fiducial == NULL) {
        fprintf(stderr, COMPRESSED_SPARSE_MATRIX_ACCESS_EXCEPTION);
        return  NULL;
    }

    Matrix* uncompressed = Matrix_create(compressed->rows, compressed->cols, MATRIX_INIT_ENABLE, fiducial);

    if (uncompressed == NULL) {
        fprintf(stderr, MATRIX_COMPRESS_OPTIONS_ERROR);
        return  NULL;
    }

    for (size_t i = 0; i < compressed->compressed_size; i++) {
        *(_Matrix_get_element_address(
                        uncompressed, 
                        compressed->units[i].row, 
                        compressed->units[i].col)
            ) = compressed->units[i].data;
    }

    return uncompressed;
}


CompressedMatrix* CompressedMatrix_create(size_t compressed_size) {
    CompressedMatrix* compressed = 
        (CompressedMatrix*) malloc (sizeof(CompressedMatrix));
    
    if (compressed == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_CREATE_ERROR);
        return NULL;
    }

    compressed->data = 
        (MatrixEleType*) malloc (sizeof(MatrixEleType) * compressed_size);

    if (compressed->data == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_CREATE_ERROR);
        return NULL;
    }

    compressed->compressed_size = compressed_size;

    return compressed;
}


int CompressedMatrix_clean(CompressedMatrix** compressed) {
    if (compressed == NULL | *compressed == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_ACCESS_EXCEPTION);
        return -1;
    }

    free((*compressed)->data);
    free(*compressed);
    *compressed = NULL;
    return 0;
}


int CompressedMatrix_display(CompressedMatrix* compressed) {
    if (compressed == NULL) {
        fprintf(stderr, COMPRESSED_MATRIX_ACCESS_EXCEPTION);
        return -1;
    }
    printf("CompressedMatrix: {  ");
    for (size_t i =0; i < compressed->compressed_size; i++) {
        printf("%d  ", compressed->data[i]);
    }
    printf("}\n");

    return 0;
}


CompressedSparseMatrix* CompressedSparseMatrix_create(Matrix* matrix, size_t compressed_size) {
    if (matrix == NULL) {
        fprintf(stderr, MATRIX_ACCESS_EXCEPTION);
        return  NULL;
    }

    CompressedSparseMatrix* compressed = (CompressedSparseMatrix*) malloc (sizeof(CompressedSparseMatrix));

    if(compressed == NULL) {
        fprintf(stderr, COMPRESSED_SPARSE_MATRIX_CREATE_ERROR);
        return NULL;
    }

    compressed->units = (CompressedSparseMatrixUnit*) malloc (sizeof(CompressedSparseMatrixUnit) * compressed_size);
    if (compressed->units == NULL) {
        fprintf(stderr, COMPRESSED_SPARSE_MATRIX_CREATE_ERROR);
        free(compressed);
        return NULL;
    }

    compressed->cols = matrix->cols;
    compressed->rows = matrix->rows;
    compressed->compressed_size = compressed_size;
    return compressed;
}


int CompressedSparseMatrix_clean(CompressedSparseMatrix** compressed) {
    if (compressed == NULL || *compressed == NULL) {
        fprintf(stderr, COMPRESSED_SPARSE_MATRIX_ACCESS_EXCEPTION);
        return -1;
    }

    free((*compressed)->units);
    free(*compressed);
    *compressed = NULL;
    return 0;
}


int CompressedSparseMatrix_display(CompressedSparseMatrix* compressed) {
    if (compressed == NULL) {
        fprintf(stderr, COMPRESSED_SPARSE_MATRIX_ACCESS_EXCEPTION);
        return -1;
    }

    printf("CompressedSparseMatrix: {  ");
    for (size_t i = 0; i < compressed->compressed_size; i++) {
        printf(
            "%d-{%lu %lu}  ",
            compressed->units[i].data,
            compressed->units[i].col,
            compressed->units[i].row
        );
    }
    printf("}\n");
}
