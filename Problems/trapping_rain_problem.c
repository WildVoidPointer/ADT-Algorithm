/*
From: 
    Algorithm Thought Book?

    
Description:
    Given a non-negative integer array `height` representing a histogram,
    where each element represents the height of a bar. 
    Compute how much rainwater can be trapped between the bars.  


Example 1:
    Input: 
        0 1 0 2 1 0 1 3 2 1 2 1

    Output: 
        6  


Example 2:
    Input: 
        4 2 0 3 2 5 
        
    Output: 
        9 


Notes:
    Each element in the array represents the height of a bar with a width of one unit.  
    Calculate the amount of water that can be trapped in the dips between the bars.
*/


#include <stdio.h>


int trapping_water_by_prefix_sum(int column_height[], int size) {
    int left_max_height[size], right_max_height[size];
    left_max_height[0] = column_height[0];
    right_max_height[size - 1] = column_height[size - 1];

    for (int i = 1; i < size; i++) {
        left_max_height[i] = 
            left_max_height[i - 1] > column_height[i] ? 
                left_max_height[i - 1] : column_height[i];
    }

    for (int i = size - 2; i >= 0; i--) {
        right_max_height[i] =
            right_max_height[i + 1] > column_height[i] ?
                right_max_height[i + 1] : column_height[i];
    }

    int sum = 0;

    for (int i = 0; i < size; i++) {
        int min = right_max_height[i] > left_max_height[i] ?
            left_max_height[i] : right_max_height[i]; 
        sum += min - column_height[i];
    }

    return sum;
}


int main(int argc, char const *argv[]){
    
    int column_height[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    printf("%d\n", trapping_water_by_prefix_sum(column_height, 12));
    return 0;
}
