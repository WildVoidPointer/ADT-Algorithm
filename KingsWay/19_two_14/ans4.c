#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct {
    int value;
    int array_index;  // 0: sl1, 1: sl2, 2: sl3
    int element_index;
} HeapNode;

void quick_sort(int array[], int left_ptr, int right_ptr);
void min_heapify(HeapNode heap[], int size, int i);
void build_min_heap(HeapNode heap[], int size);

int get_minimum_distance_point(int l1, int sl1[], int l2, int sl2[], int l3, int sl3[]) {
    // 排序三个数组
    quick_sort(sl1, 0, l1 - 1);
    quick_sort(sl2, 0, l2 - 1);
    quick_sort(sl3, 0, l3 - 1);
    
    // 初始化堆
    HeapNode heap[3] = {
        {sl1[0], 0, 0},
        {sl2[0], 1, 0},
        {sl3[0], 2, 0}
    };
    build_min_heap(heap, 3);
    
    int min_distance = INT_MAX;
    int pointers[3] = {0, 0, 0};  // 各数组的当前指针
    
    while (1) {
        // 获取当前最小元素
        HeapNode min_node = heap[0];
        int a = (min_node.array_index == 0) ? sl1[min_node.element_index] : 
               (min_node.array_index == 1) ? sl2[min_node.element_index] : sl3[min_node.element_index];
        
        // 计算当前三元组的max和min
        int current_max = INT_MIN;
        int current_min = INT_MAX;
        for (int i = 0; i < 3; i++) {
            int val = (i == 0) ? sl1[pointers[i]] : 
                     (i == 1) ? sl2[pointers[i]] : sl3[pointers[i]];
            if (val > current_max) current_max = val;
            if (val < current_min) current_min = val;
        }
        
        int current_distance = 2 * (current_max - current_min);
        if (current_distance < min_distance) {
            min_distance = current_distance;
            if (min_distance == 0) return 0;
        }
        
        // 移动最小元素所在数组的指针
        int array_idx = min_node.array_index;
        pointers[array_idx]++;
        
        // 检查是否越界
        if ((array_idx == 0 && pointers[0] >= l1) ||
            (array_idx == 1 && pointers[1] >= l2) ||
            (array_idx == 2 && pointers[2] >= l3)) {
            break;
        }
        
        // 更新堆顶元素
        heap[0].value = (array_idx == 0) ? sl1[pointers[array_idx]] : 
                        (array_idx == 1) ? sl2[pointers[array_idx]] : sl3[pointers[array_idx]];
        heap[0].element_index = pointers[array_idx];
        
        // 维护堆性质
        min_heapify(heap, 3, 0);
    }
    
    return min_distance;
}

// 最小堆维护
void min_heapify(HeapNode heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < size && heap[left].value < heap[smallest].value) {
        smallest = left;
    }
    if (right < size && heap[right].value < heap[smallest].value) {
        smallest = right;
    }
    
    if (smallest != i) {
        HeapNode temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        min_heapify(heap, size, smallest);
    }
}

// 构建最小堆
void build_min_heap(HeapNode heap[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        min_heapify(heap, size, i);
    }
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