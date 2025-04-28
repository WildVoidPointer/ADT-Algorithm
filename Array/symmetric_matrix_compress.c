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
    int size, SymmetricMatrixCompressBean origin[size][size]) {
        
    SymmetricMatrixCompressBean* bean = 
        (SymmetricMatrixCompressBean*) malloc 
            (sizeof(SymmetricMatrixCompressBean) * (size + 1) * (size) / 2);

    if (bean == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for compression.\n");
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
            bean[index++] = origin[i][j];
        }
    }
    return bean;
}


int calculate_matrix_size(int compressed_size) {
    return (compressed_size >= 0) ? ((int)sqrt(1 + compressed_size * 8) - 1) / 2 : -1;
}


SymmetricMatrixCompressBean*
symmetric_matrix_uncompress(SymmetricMatrixCompressBean* origin, int size) {
    int compress_size = calculate_matrix_size(size);
    if (compress_size == -1) {
        return NULL;
    }

}


void symmetric_matrix_display(SymmetricMatrixCompressBean** bean, int size) {
    printf("SymmetricMatrix:\n");
    for (int i = 0; i < size; i++) {
        printf("    { ");
        for (int j = 0; j < size; j++) {
            printf("%d ", bean[i][j]);
        }
        printf("}\n");
    }
}


void free_matrix(SymmetricMatrixCompressBean** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


int main() {
    SymmetricMatrixCompressBean* compressed = symmetric_matrix_compress(4, ORIGIN_MATRIX);
    if (!compressed) return -1;

    printf("Compressed Matrix:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");

    return 0;
}
