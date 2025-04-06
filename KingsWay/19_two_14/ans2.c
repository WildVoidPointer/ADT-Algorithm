#include <stdio.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void quick_sort(int array[], int left_ptr, int right_ptr);

int get_minimum_distance_point(int l1, int sl1[], int l2, int sl2[], int l3, int sl3[]) {

    quick_sort(sl1, 0, l1 - 1);
    quick_sort(sl2, 0, l2 - 1);
    quick_sort(sl3, 0, l3 - 1);

    int i = 0, j = 0, k = 0;
    int min_distance = INT_MAX;

    while (i < l1 && j < l2 && k < l3) {
        int a = sl1[i], b = sl2[j], c = sl3[k];
        int current_max = MAX(MAX(a, b), c);
        int current_min = MIN(MIN(a, b), c);
        int current_distance = 2 * (current_max - current_min);

        if (current_distance < min_distance) {
            min_distance = current_distance;
            if (min_distance == 0) return 0;
        }

        if (a <= b && a <= c) {
            i++;
        } else if (b <= a && b <= c) {
            j++;
        } else {
            k++;
        }
    }

    return min_distance;
}


void quick_sort(int array[], int left_ptr, int right_ptr) {
    if (left_ptr >= right_ptr) 
        return;
    
    int _pivot_ptr = (left_ptr + right_ptr) / 2;
    int pivot_ele = array[_pivot_ptr];
    int _left_ptr = left_ptr;
    int _right_ptr = right_ptr;

    while (_left_ptr <= _right_ptr) {
        while (array[_left_ptr] < pivot_ele) {
            _left_ptr++;
        }
        while (array[_right_ptr] > pivot_ele) {
            _right_ptr--;
        }
        if (_left_ptr <= _right_ptr) {
            int _temp = array[_left_ptr];
            array[_left_ptr] = array[_right_ptr];
            array[_right_ptr] = _temp;
            _left_ptr++;
            _right_ptr--;
        }
    }
    quick_sort(array, left_ptr, _right_ptr);
    quick_sort(array, _left_ptr, right_ptr);
}


int main() {
    int sl1[] = {-1, 0, 9};
    int sl2[] = {-25, -10, 10, 11};
    int sl3[] = {2, 9, 17, 30, 41};

    printf("%d\n", get_minimum_distance_point(3, sl1, 4, sl2, 4, sl3));
}
