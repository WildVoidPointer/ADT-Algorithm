#include "matrix.h"


MatrixDataType TRIDIAGONAL_TEST_MATRIX[5][5] = {
    {1, 2, 0, 0, 0},
    {3, 4, 5, 0, 0},
    {0, 6, 7, 8, 0},
    {0, 0, 9, 10, 11},
    {0, 0, 0, 12, 13}
};


MatrixDataType SYMMETRIC_TEST_MATRIX[4][4] = {
    {1, 2, 4, 6},
    {2, 3, 5, 7},
    {4, 5, 6, 8},
    {7, 8, 9, 10}
};


MatrixDataType LOWER_TRIANGULAR_TEST_MATRIX[4][4] = {
    {1, 9, 9, 9},
    {2, 3, 9, 9},
    {4, 5, 6, 9},
    {7, 8, 9, 10}
};


MatrixDataType UPPER_TRIANGULAR_TEST_MATRIX[4][4] = {
    {1, 2, 3, 4},
    {8, 5, 6, 7},
    {8, 8, 8, 9},
    {8, 8, 8, 10}
};


MatrixDataType SPARSE_TEST_MATRIX[5][5] = {
    {0, 0, 3, 0, 0},
    {0, 0, 0, 0, 7},
    {1, 0, 0, 0, 0},
    {0, 0, 0, 5, 0},
    {0, 2, 0, 0, 0}
};


int main(int argc, char const *argv[])
{
    MatrixDataType default_filler = 0;

    Matrix* tridiagonal_matrix = Matrix_build_of_array(5, 5, TRIDIAGONAL_TEST_MATRIX);

    CompressedMatrix* tridaigonal_compressed = Matrix_compress_tridiagonal_matrix(
        tridiagonal_matrix
    );

    Matrix* tridaigonal_uncompressed = Matrix_uncompress_tridiagonal_matrix(
        tridaigonal_compressed, &default_filler
    );

    CompressedMatrix_display(tridaigonal_compressed);
    Matrix_display(tridaigonal_uncompressed);

    Matrix_destroy(&tridiagonal_matrix);
    Matrix_destroy(&tridaigonal_uncompressed);
    printf("Matrix destroy result: %p\n", tridiagonal_matrix);

    CompressedMatrix_destroy(&tridaigonal_compressed);
    printf("CompressedMatrix destroy result: %p\n", tridaigonal_compressed);
    printf("-----\n");


    Matrix* origin_matrix = Matrix_build_of_array(4, 4, SYMMETRIC_TEST_MATRIX);
    Matrix* copied_matrix = Matrix_copy(origin_matrix);
    Matrix_display(origin_matrix);
    Matrix_display(copied_matrix);
    Matrix_add(origin_matrix, copied_matrix);
    Matrix_display(origin_matrix);

    Matrix_subtract(origin_matrix, copied_matrix);
    Matrix_display(origin_matrix);

    Matrix* multiply_result = Matrix_multiply(origin_matrix, origin_matrix);
    Matrix_display(multiply_result);

    Matrix_destroy(&origin_matrix);
    Matrix_destroy(&copied_matrix);
    Matrix_destroy(&multiply_result);
    printf("-----\n");


    Matrix* symmetric_matrix = Matrix_build_of_array(4, 4, SYMMETRIC_TEST_MATRIX);
    CompressedMatrix* symmetric_compressed = Matrix_compress_symmetric_matrix(
        symmetric_matrix
    );

    Matrix* symmetric_uncompressed = Matrix_uncompress_symmetric_matrix(
        symmetric_compressed, &default_filler
    );

    CompressedMatrix_display(symmetric_compressed);
    Matrix_display(symmetric_uncompressed);
    Matrix_destroy(&symmetric_matrix);
    Matrix_destroy(&symmetric_uncompressed);
    CompressedMatrix_destroy(&symmetric_compressed);
    printf("-----\n");


    Matrix* lower = Matrix_build_of_array(4, 4, LOWER_TRIANGULAR_TEST_MATRIX);
    CompressedMatrix* lower_compressed = Matrix_compress_lower_triangular_matrix(lower);
    Matrix* lower_uncompressed = Matrix_uncompress_lower_triangular_matrix(
        lower_compressed, &default_filler
    );
    CompressedMatrix_display(lower_compressed);
    Matrix_display(lower_uncompressed);
    CompressedMatrix_destroy(&lower_compressed);
    Matrix_destroy(&lower_uncompressed);
    Matrix_destroy(&lower);
    printf("-----\n");


    Matrix* upper = Matrix_build_of_array(4, 4, UPPER_TRIANGULAR_TEST_MATRIX);
    CompressedMatrix* upper_compressed = Matrix_compress_upper_triangular_matrix(upper);
    Matrix* upper_uncompressed = Matrix_uncompress_upper_triangular_matrix(
        upper_compressed, &default_filler
    );
    CompressedMatrix_display(upper_compressed);
    Matrix_display(upper_uncompressed);
    Matrix_destroy(&upper);
    Matrix_destroy(&upper_uncompressed);
    CompressedMatrix_destroy(&upper_compressed);

    printf("-----\n");


    Matrix* sparse = Matrix_build_of_array(5, 5, SPARSE_TEST_MATRIX);
    CompressedSparseMatrix* sparse_compressed = Matrix_compress_sparse_matrix(
        sparse, &default_filler
    );
    Matrix* sparse_uncompressed = Matrix_uncompress_sparse_matrix(
        sparse_compressed, &default_filler
    );
    CompressedSparseMatrix_display(sparse_compressed);
    Matrix_display(sparse_uncompressed);
    Matrix_destroy(&sparse);
    Matrix_destroy(&sparse_uncompressed);
    CompressedSparseMatrix_destroy(&sparse_compressed);

    return 0;
}
