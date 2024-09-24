#include <stdio.h>

#define MAX_LEN 1000010 

int G_EFFECTIVE_LEN;
int G_ARRAY[MAX_LEN];

void quick_sort(int array[], int left_ptr, int right_ptr) {
    if (left_ptr >= right_ptr) 
        return;
    
    int pivot = (left_ptr + right_ptr) / 2;
    int median_value = array[pivot];
    int _left_ptr = left_ptr;
    int _right_ptr = right_ptr;

    while (_left_ptr <= _right_ptr) {
        while (array[_left_ptr] < median_value) {
            _left_ptr++;
        }
        while (array[_right_ptr] > median_value) {
            _right_ptr--;
        }
        if (_left_ptr <= _right_ptr) {
            int temp = array[_left_ptr];
            array[_left_ptr] = array[_right_ptr];
            array[_right_ptr] = temp;
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

