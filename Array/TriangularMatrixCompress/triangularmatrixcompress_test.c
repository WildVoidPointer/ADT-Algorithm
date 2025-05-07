#include "triangularmatrixcompress.h"


TriangularMatrixBean LOWER_TRIANGULAR_MATRIX[4][4] = {
    {1, 9, 9, 9},
    {2, 3, 9, 9},
    {4, 5, 6, 9},
    {7, 8, 9, 10}
};

TriangularMatrixBean UPPER_TRIANGULAR_MATRIX[4][4] = {
    {1, 2, 3, 4},
    {8, 5, 6, 7},
    {8, 8, 8, 9},
    {8, 8, 8, 10}
};


int main() {
    TriangularMatrixBean* lower_compressed = 
        lower_triangular_matrix_compress(4, LOWER_TRIANGULAR_MATRIX);

    TriangularMatrixBean** lower_uncompressed = 
        lower_triangular_matrix_uncompress(11, lower_compressed);

    triangular_matrix_compressed_bean_display(11, lower_compressed);

    triangular_matrix_uncompressed_bean_display(4, lower_uncompressed);

    triangular_matrix_compressed_bean_clean(&lower_compressed);

    triangular_matrix_uncompressed_bean_clean(4, &lower_uncompressed);

    TriangularMatrixBean* upper_compressed = 
        upper_triangular_matrix_compress(4, UPPER_TRIANGULAR_MATRIX);

    TriangularMatrixBean** upper_uncompressed =
        upper_triangular_matrix_uncompressed(11, upper_compressed);

    triangular_matrix_compressed_bean_display(11, upper_compressed);

    triangular_matrix_uncompressed_bean_display(4, upper_uncompressed);

    triangular_matrix_compressed_bean_clean(&upper_compressed);

    triangular_matrix_uncompressed_bean_clean(4, &upper_uncompressed);

    return 0;
}