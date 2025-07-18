#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"


Matrix* 
Matrix_create(size_t rows, size_t cols, 
    MatrixInitModeEnum is_init, MatrixEleType* init_data) {

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
Matrix_build_of_stack(size_t rows, size_t cols, 
    MatrixEleType (*stack_matrix)[cols]) {

    Matrix* matrix = 
        Matrix_create(rows, cols, MATRIX_INIT_DISABLE, NULL);

    if (matrix == NULL) {
        fprintf(stderr, MATRIX_CREATE_ERROR);
        return NULL;
    }

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix->data[i * cols + j] = stack_matrix[i][j];
        }
    }

    return matrix;
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
        return 0;
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
                        matrix->data[i * matrix->rows + j];
            }
        }
    }

    return compressed;
}


Matrix* 
Matrix_uncompress_tridiagonal_matrix(
    CompressedMatrix* compressed, MatrixEleType* filler) {

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
                matrix->data[i * matrix->rows + j] = compressed->data[compressed_offset++];
            } else {
                matrix->data[i * matrix->rows + j] = *filler;
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
        return 0;
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
                matrix->data[i * matrix->rows + j];
        }
    }

    return compressed;
}


Matrix* Matrix_uncompress_symmetric_matrix(
    CompressedMatrix* compressed, MatrixEleType* filler) {
    
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
            matrix->data[i * matrix->rows + j] = 
                matrix->data[j * matrix->rows + i] =
                compressed->data[compressed_offset++];
        }
    }

    return matrix;
}


int Matrix_clean(Matrix** matrix) {
    if (matrix == NULL || *matrix == NULL) {
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
            printf("%d  ", matrix->data[i * matrix->cols + j]);
        }
        printf("}\n");
    }
    printf("}\n");
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
