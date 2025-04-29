#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int SymmetricMatrixCompressBean;

SymmetricMatrixCompressBean ORIGIN_MATRIX[4][4] = {
    {1, 3, 4, 5},
    {3, 2, 6, 7},
    {4, 6, 3, 8},
    {5, 7, 8, 4}
};


SymmetricMatrixCompressBean* 
symmetric_matrix_compress(
    int rows, SymmetricMatrixCompressBean uncompressed[rows][rows]) {
        
    SymmetricMatrixCompressBean* compressed = 
        (SymmetricMatrixCompressBean*) malloc 
            (sizeof(SymmetricMatrixCompressBean) * (rows + 1) * (rows) / 2);

    if (compressed == NULL) {
        fprintf(
            stderr, 
            "Error: Failed to allocate memory for compression.\n"
        );

        return NULL;
    }

    int compressed_offset = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            compressed[compressed_offset++] = uncompressed[i][j];
        }
    }
    return compressed;
}


int calculate_uncompressed_matrix_size(int compressed_size) {
    return (compressed_size >= 0) ? 
        ((int)sqrt(1 + compressed_size * 8) - 1) / 2 : -1;
}


SymmetricMatrixCompressBean*
symmetric_matrix_uncompress(
    SymmetricMatrixCompressBean* compressed, int compressed_size) {

    int rows = calculate_uncompressed_matrix_size(compressed_size);
    if (rows == -1) {
        return NULL;
    }

    SymmetricMatrixCompressBean** uncompressed =
        (SymmetricMatrixCompressBean**) malloc
            (sizeof(SymmetricMatrixCompressBean*) * rows);

    if (uncompressed == NULL) {
        fprintf(
            stderr, 
            "Error: Failed to allocate memory for compression.\n"
        );
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        uncompressed[i] = (SymmetricMatrixCompressBean*) malloc
            (sizeof(SymmetricMatrixCompressBean) * rows);
            
        if (uncompressed[i] == NULL) {
            fprintf(
                stderr, 
                "Error: Failed to allocate memory for compression.\n"
            );
            for (int j = 0; j < i; j++) {
                free(uncompressed[j]);
            }
            free(uncompressed);
            return NULL;
        }
    }
}


SymmetricMatrixCompressBean*
symmetric_matrix_flat_uncompress(
    SymmetricMatrixCompressBean* compressed, int compressed_size) {

    int rows = calculate_uncompressed_matrix_size(compressed_size);
    if (rows == -1) {
        return NULL;
    }

    SymmetricMatrixCompressBean* uncompressed = 
        (SymmetricMatrixCompressBean*) malloc 
        (sizeof(SymmetricMatrixCompressBean) * rows * rows);

    if (uncompressed == NULL) {
        fprintf(
            stderr, 
            "Error: Failed to allocate memory for compression.\n"
        );
        return NULL;
    }

    int compress_offset = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            uncompressed[i * rows + j] 
                = uncompressed[j * rows + i] 
                = compressed[compress_offset++];
        }
    }
    return uncompressed;
}


void 
symmetric_matrix_flat_display(
    SymmetricMatrixCompressBean* flat_matrix, int raws) {

    printf("SymmetricMatrix:  {\n");
    for (int i = 0; i < raws; i++) {
        printf("    { ");
        for (int j = 0; j < raws; j++) {
            printf("%d ", flat_matrix[i * raws + j]);
        }
        printf("}\n");
    }
    printf("}\n");
}


void free_matrix(SymmetricMatrixCompressBean** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


int main() {
    int size = 4;
    SymmetricMatrixCompressBean* compressed = 
        symmetric_matrix_compress(size, ORIGIN_MATRIX);

    if (!compressed) return -1;

    printf("Compressed Matrix:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");

    SymmetricMatrixCompressBean* flat_uncompressed = 
        symmetric_matrix_flat_uncompress(compressed, 10);

    symmetric_matrix_flat_display(flat_uncompressed, size);

    return 0;
}
