#include "symmetricmatrixcompress.h"


SymmetricMatrixBean ORIGIN_MATRIX[4][4] = {
    {1, 3, 4, 5},
    {3, 2, 6, 7},
    {4, 6, 3, 8},
    {5, 7, 8, 4}
};


int main() {
    int size = 4;
    SymmetricMatrixBean* compressed = 
        symmetric_matrix_compress(size, ORIGIN_MATRIX);

    if (!compressed) return -1;

    printf("Compressed Matrix:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");

    SymmetricMatrixBean* flat_uncompressed = 
        symmetric_matrix_flat_uncompress(compressed, 10);

    symmetric_matrix_flat_display(flat_uncompressed, size);

    symmetric_matrix_flat_bean_clean(&compressed);
    symmetric_matrix_flat_bean_clean(&flat_uncompressed);

    return 0;
}