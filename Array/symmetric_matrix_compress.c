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
symmetric_matrix_rows_compress(int size, SymmetricMatrixCompressBean origin[][size]) {
    SymmetricMatrixCompressBean* bean = 
        (SymmetricMatrixCompressBean*) malloc(sizeof(SymmetricMatrixCompressBean) * size * (size + 1) / 2);

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
    int n = (int)((sqrt(8 * compressed_size + 1) - 1) / 2);
    return (n * (n + 1) / 2 == compressed_size) ? n : -1;
}


SymmetricMatrixCompressBean** 
symmetric_matrix_rows_uncompress(SymmetricMatrixCompressBean* origin, int compressed_size) {
    int side = calculate_matrix_size(compressed_size);
    if (side == -1) {
        fprintf(stderr, "Error: Invalid compressed size.\n");
        return NULL;
    }

    SymmetricMatrixCompressBean** bean = 
        (SymmetricMatrixCompressBean**) malloc(sizeof(SymmetricMatrixCompressBean*) * side);
        
    if (bean == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }

    for (int i = 0; i < side; i++) {
        bean[i] = (SymmetricMatrixCompressBean*) malloc(sizeof(SymmetricMatrixCompressBean) * side);
        if (bean[i] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(bean[j]);
            }
            free(bean);
            return NULL;
        }
    }

    for (int i = 0, index = 0; i < side; i++) {
        for (int j = 0; j <= i; j++) {
            bean[i][j] = bean[j][i] = origin[index++];
        }
    }
    return bean;
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
    SymmetricMatrixCompressBean* compressed = symmetric_matrix_rows_compress(4, ORIGIN_MATRIX);
    if (!compressed) return 1;

    printf("Compressed Matrix:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", compressed[i]);
    }
    printf("\n");

    SymmetricMatrixCompressBean** uncompressed = symmetric_matrix_rows_uncompress(compressed, 10);
    if (!uncompressed) {
        free(compressed);
        return 1;
    }

    symmetric_matrix_display(uncompressed, 4);

    free(compressed);
    free_matrix(uncompressed, 4);

    return 0;
}
