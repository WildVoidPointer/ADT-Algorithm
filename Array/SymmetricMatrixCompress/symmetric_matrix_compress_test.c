#include "symmetric_matrix_compress.h"


SymmetricMatrixBean ORIGIN_MATRIX[4][4] = {
    {1, 3, 4, 5},
    {3, 2, 6, 7},
    {4, 6, 3, 8},
    {5, 7, 8, 4}
};


int main() {
    int rows = 4;
    int compressed_size = 10;

    SymmetricMatrixBean* compressed = 
        symmetric_matrix_compress(rows, ORIGIN_MATRIX);

    SymmetricMatrixBean** uncompressed =
        symmetric_matrix_uncompress(compressed_size, compressed);

    if (!compressed) return -1;
    if (!uncompressed) return -1;

    symmetric_matrix_compressed_bean_display(compressed_size, compressed);
    symmetric_matrix_uncompressed_bean_display(rows, uncompressed);

    symmetric_matrix_compressed_bean_clean(&compressed);
    symmetric_matrix_uncompressed_bean_clean(rows, &uncompressed);

    return 0;
}