#include <stdio.h>

#define MAX_LEN 1000010 


int G_EFFECTIVE_LEN = 0;
int G_ARRAY[MAX_LEN] = {0};


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


int main()
{
    scanf("%d",&G_EFFECTIVE_LEN);
    
    for(int i = 0 ; i < G_EFFECTIVE_LEN ; i++)
    {
        scanf("%d",&G_ARRAY[i]);
    }
    
    quick_sort(G_ARRAY , 0 , G_EFFECTIVE_LEN-1);
    
    for(int i = 0 ; i < G_EFFECTIVE_LEN ; i++)
    {
        printf("%d ", G_ARRAY[i]); 
    }
    
    return 0;
}

