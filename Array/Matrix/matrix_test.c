#include "matrix.h"


MatrixEleType TRIDIAGONAL_TEST_MATRIX[5][5] = {
    {1, 2, 0, 0, 0},
    {3, 4, 5, 0, 0},
    {0, 6, 7, 8, 0},
    {0, 0, 9, 10, 11},
    {0, 0, 0, 12, 13}
};


MatrixEleType SYMMETRIC_TEST_MATRIX[4][4] = {
    {1, 2, 4, 6},
    {2, 3, 5, 7},
    {4, 5, 6, 8},
    {7, 8, 9, 10}
};


int main(int argc, char const *argv[])
{
    MatrixEleType default_filler = 0;

    Matrix* tridiagonal_matrix = Matrix_build_of_stack(5, 5, TRIDIAGONAL_TEST_MATRIX);
    CompressedMatrix* tridaigonal_compressed = Matrix_compress_tridiagonal_matrix(tridiagonal_matrix);
    Matrix* tridaigonal_uncompressed = Matrix_uncompress_tridiagonal_matrix(tridaigonal_compressed, &default_filler);
    CompressedMatrix_display(tridaigonal_compressed);
    Matrix_display(tridaigonal_uncompressed);
    Matrix_clean(&tridiagonal_matrix);
    Matrix_clean(&tridaigonal_uncompressed);
    printf("Matrix clean result: %p\n", tridiagonal_matrix);
    CompressedMatrix_clean(&tridaigonal_compressed);
    printf("CompressedMatrix clean result: %p\n", tridaigonal_compressed);


    Matrix* symmetric_matrix = Matrix_build_of_stack(4, 4, SYMMETRIC_TEST_MATRIX);
    CompressedMatrix* symmetric_compressed = Matrix_compress_symmetric_matrix(symmetric_matrix);
    Matrix* symmetric_uncompressed = Matrix_uncompress_symmetric_matrix(symmetric_compressed, &default_filler);
    CompressedMatrix_display(symmetric_compressed);
    Matrix_display(symmetric_uncompressed);
    Matrix_clean(&symmetric_matrix);
    Matrix_clean(&symmetric_uncompressed);
    CompressedMatrix_clean(&symmetric_compressed);


    return 0;
}
