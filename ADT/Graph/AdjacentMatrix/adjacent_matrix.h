#ifndef ADJACENT_MATRIX_H_
#define ADJACENT_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>


typedef int AdjacentVertex;


typedef struct AdjacentMatrix {
    AdjacentVertex* vertexes;
    int vertex_num;
} AdjacentMatrix;
 

#endif
