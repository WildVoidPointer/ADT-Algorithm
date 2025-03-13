#include <stdio.h>
#include <stdlib.h>


typedef int SymmetricMatrixCompressBean;


SymmetricMatrixCompressBean ORIGIN_MATRIX[4][4] = {
    {1, 3, 4, 5},
    {3, 2, 6, 7},
    {4, 6, 3, 8},
    {5, 7, 8, 4}
};


SymmetricMatrixCompressBean* 
symmetric_matrix_compresser(size_t size, SymmetricMatrixCompressBean origin[][size]) {
    SymmetricMatrixCompressBean* bean = 
        (SymmetricMatrixCompressBean*) malloc 
            (sizeof(SymmetricMatrixCompressBean) * size * (size + 1) / 2);

    if (bean == NULL) {
        fprintf(
            stderr,
            "SymmetricMatrixCompressBeanInitError: Failed to allocate memory for the `Bean`"
        );
        return NULL;
    }

    size_t index = 0;

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j <= i; j++) {
            bean[index++] = origin[i][j];
        }
    }

    return bean;
}


int main(int argc, char const *argv[])
{
    SymmetricMatrixCompressBean* bean = symmetric_matrix_compresser(4, ORIGIN_MATRIX);
    for (size_t i = 0; i < 10; i++) {
        printf("%d  ", bean[i]);
    }
    free(bean);
    return 0;
}


