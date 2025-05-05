#include "triangularmatrixcompress.h"


TriangularMatrixBean LOWER_TRIANGULAR_MATRIX[4][4] = {
    {1, 9, 9, 9},
    {2, 3, 9, 9},
    {4, 5, 6, 9},
    {7, 8, 9, 10}
};


int main() {
    TriangularMatrixBean* compressed = 
        lower_triangular_matrix_compress(4, LOWER_TRIANGULAR_MATRIX);

    for (int i = 0; i < 11; i++) {
        printf("%d  ", compressed[i]);
    }
    printf("\n");

    triangular_matrix_flat_bean_clean(&compressed);
}