#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int a;
    int b;
    int c;
} Point;


int get_distance(int a, int b, int c) {
    return abs(a - b) + abs(b - c) + abs(c - a);
}


int get_minimum_distance(int size, int sl[]) {
    int select = sl[0];
    for (int i = 1; i < size; i++) {
        if (sl[i] < select) {
            select = sl[i];
        }
    }
    return select;
}


int
get_minimum_distance_point(
    int l1, int sl1[], int l2, int sl2[], int l3, int sl3[]) {

    int res[l1];
    int res_index = 0;
    int distance[l2 * l3];
    int t_index = 0;
    for (int i = 0; i < l1; i++) {
        for (int j = 0; j < l2; j++) {
            for (int k = 0; k < l3; k++) {
                distance[t_index++] = get_distance(sl1[i], sl2[j], sl3[k]);
            }
        }
        res[res_index++] = get_minimum_distance(l2 *l3, distance);
        t_index = 0;
    }
    return get_minimum_distance(l1, res);
}


int main() {
    int sl1[] = {1, 5};
    int sl2[] = {3, 7};
    int sl3[] = {2, 6};

    printf("%d\n", get_minimum_distance_point(2, sl1, 2, sl2, 2, sl3));
}