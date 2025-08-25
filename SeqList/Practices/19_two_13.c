#include <stdio.h>


void quick_sort_with_fixed_partition(int array[], int left_ptr, int right_ptr) {
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
    quick_sort_with_fixed_partition(array, left_ptr, _right_ptr);
    quick_sort_with_fixed_partition(array, _left_ptr, right_ptr);
}


int 
calculate_smallest_non_occurrence_positive_integer1(int size, int sl[]) {
    if (size == 0) {
        return 1;
    }

    quick_sort_with_fixed_partition(sl, 0, size - 1);
    int index = 0;
    
    while (index < size && sl[index] <= 0) {
        index++;
    }


    if (index >= size || sl[index] != 1) {
        return 1;
    }

    for (int i = index; i < size - 1; i++) {
        if (sl[i + 1] > sl[i] + 1) {
            return sl[i] + 1;
        }
    }
    
    return sl[size - 1] + 1;
}


int 
calculate_smallest_non_occurrence_positive_integer2(int size, int nums[]) {
    if (size == 0) {
        return 1;
    }

    for (int i = 0; i < size; i++) {
        while (nums[i] >= 1 && nums[i] <= size && nums[i] != nums[nums[i] - 1]) {
            int temp = nums[i];
            nums[i] = nums[temp - 1];
            nums[temp - 1] = temp;
        }
    }

    for (int i = 0; i < size; i++) {
        if (nums[i] != i + 1) {
            return i + 1;
        }
    }

    return size + 1;
}


int main() {
    int sl1[] = {-5, 3, 2, 3};
    int sl2[] = {1, 2, 3};

    printf("%d\n", calculate_smallest_non_occurrence_positive_integer2(3, sl2));
}