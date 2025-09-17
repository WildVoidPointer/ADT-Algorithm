/* 
From: 
    https://leetcode.com/problems/minimum-operations-to-make-array-equal/description/


Description:
    You have an array arr of length n where arr[i] = (2 * i) + 1 for all valid values of i (i.e., 0 <= i < n).
    In one operation, you can select two indices x and y where 0 <= x, y < n 
    and subtract 1 from arr[x] and add 1 to arr[y] (i.e., perform arr[x] -=1 and arr[y] += 1). 
    The goal is to make all the elements of the array equal. 
    It is guaranteed that all the elements of the array can be made equal using some operations.

    Given an integer n, the length of the array, 
    return the minimum number of operations needed to make all the elements of arr equal.


Example 1:
    Input: n = 3
    Output: 2
    Explanation: arr = [1, 3, 5]
        First operation choose x = 2 and y = 0, this leads arr to be [2, 3, 4]
        In the second operation choose x = 2 and y = 0 again, thus arr = [3, 3, 3].

        
Example 2:
    Input: n = 6
    Output: 9
    

Constraints:
    1 <= n <= 10^4
*/


#include <stdio.h>
#include <stdlib.h>


int conventional_simulation(int n) {
    int *array = (int*) malloc (sizeof(int) * n);
    int step = 0;
    int pivot_pos = n / 2;

    for (int i = 0; i < n; i++) {
        array[i] = (2 * i) + 1;
    }

    if ((n % 2) == 0) {
        int pivot_var = ((array[pivot_pos] + array[pivot_pos - 1]) / 2);

        for (int i = 0; i < pivot_pos; i++) {
            step += pivot_var - array[i];
        }
    }

    if ((n % 2) != 0) {
        int pivot_var = array[pivot_pos];
        
        for (int i = 0; i < pivot_pos; i++) {
            step += pivot_var - array[i];
        }
    }

    free(array);

    return step;
}


int mathematical_verification1(int n) {
    int end = n / 2;
    int step = 0;

    if ((n % 2) == 0) {
        for (int i = 0; i < end; i++) {
            step += (2 * i) + 1;
        }
    }

    if ((n % 2) != 0) {
        for (int i = 1; i <= end; i++) {
            step += (2 * i);
        }
    }

    return step;
}


int mathematical_verification2(int n) {
    int end = n / 2;

    if ((n % 2) == 0) {
        return end * end;
    } else {
        return end * end + end;
    }
}


int bit_operation(int n) {
    return (n * n - (n & 1)) >> 2;
}


int main(int argc, char const *argv[]) {

    printf("%d", mathematical_verification1(8));
    return 0;
}



