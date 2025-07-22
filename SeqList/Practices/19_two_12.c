#include <stdio.h>


int search_main_element1(int size, int sl[]) {
    int t_store = 0;
    int count = 0;

    for (int i = 0; i < size; i++) {
        t_store = sl[i];
        for (int j = 0; j < size; j++) {
            if (sl[j] == t_store) {
                count++;
            }
        }
        if (count > size / 2) {
            return t_store;
        } else {
            count = 0;
        }
    }
    return -1;
}


int search_main_element2(int size, int sl[]) {
    int candidate = -1;
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (count == 0) {
            candidate = sl[i];
            count = 1;
        } else if (sl[i] == candidate) {
            count++;
        } else {
            count--;
        }
    }


    count = 0;
    for (int i = 0; i < size; i++) {
        if (sl[i] == candidate) {
            count++;
        }
    }

    return (count > size / 2) ? candidate : -1;
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


int search_main_element3(int size, int sl[]) {
    quick_sort(sl, 0, size -1);
    int candidate = sl[size / 2];
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (sl[i] == candidate) {
            count++;
        }
    }
    return (count > size / 2) ? candidate : -1;
}




int main() {
    int size = 8;
    int sl[] = {0, 5, 5, 3, 5, 1, 5, 7};

    printf("%d\n", search_main_element1(size, sl));
}