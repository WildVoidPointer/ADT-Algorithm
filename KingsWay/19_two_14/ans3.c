#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void quick_sort(int array[], int left_ptr, int right_ptr);


int find_closest(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    int closest = arr[0];
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (abs(arr[mid] - target) < abs(closest - target)) {
            closest = arr[mid];
        }
        
        if (arr[mid] == target) {
            return arr[mid];
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    // 检查相邻元素是否更接近
    if (left < size && abs(arr[left] - target) < abs(closest - target)) {
        closest = arr[left];
    }
    if (right >= 0 && abs(arr[right] - target) < abs(closest - target)) {
        closest = arr[right];
    }
    
    return closest;
}

int get_minimum_distance_point(int l1, int sl1[], int l2, int sl2[], int l3, int sl3[]) {

    quick_sort(sl2, 0, l2 - 1);
    quick_sort(sl3, 0, l3 - 1);
    
    int min_distance = INT_MAX;
    
    for (int i = 0; i < l1; i++) {
        int a = sl1[i];
        // 在sl2中找到最接近a的元素
        int b = find_closest(sl2, l2, a);
        // 在sl3中找到最接近a的元素
        int c = find_closest(sl3, l3, a);
        
        int current_max = MAX(MAX(a, b), c);
        int current_min = MIN(MIN(a, b), c);
        int current_distance = 2 * (current_max - current_min);
        
        if (current_distance < min_distance) {
            min_distance = current_distance;
            if (min_distance == 0) return 0;
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