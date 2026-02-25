#include "./array_utils/array_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct RadixSortQ{
    int* q;
    int idx;
} RadixSortQ;


int get_integer_specified_num(int num, int digit) {
    if (digit < 1) {
        return 0;
    }

    unsigned long long power = 1;

    int abs_num = abs(num);

    for (int i = 1; i < digit; i++) {
        power = power * 10;

        if (power > abs_num) {
            return 0;
        }
    }

    return (abs_num / power) % 10;
}


void radix_sort_with_sequence_storage(
    int arr[], int len, int digit, int sp
) {

    RadixSortQ** qs = (RadixSortQ**) malloc (sizeof(RadixSortQ*) * 10);

    for (int i = 0; i < 10; i++) {
        qs[i] = (RadixSortQ*) malloc (sizeof(RadixSortQ));
        qs[i]->q = (int*) malloc (sizeof(int) * len);
        qs[i]->idx = 0;

        for (int j = 0; j < len; j++) {
            qs[i]->q[j] = sp;
        }
    }

    int qs_idx = 0;
    int arr_static_idx = 0;

    for (int curr_digit = 1; curr_digit <= digit; curr_digit++) {
        for (int arr_idx = 0; arr_idx < len; arr_idx++) {
            qs_idx = get_integer_specified_num(arr[arr_idx], curr_digit);
            RadixSortQ* rq = qs[qs_idx];
            rq->q[rq->idx++] = arr[arr_idx];
        }

        for (int i = 0; i < 10; i++) {
            RadixSortQ* rq = qs[i];
            for (int j = 0; j < rq->idx; j++) {
                arr[arr_static_idx++] = rq->q[j];
            }
            rq->idx = 0;
        }

        arr_static_idx = 0;
    }
}


int main() {
    int test_array1[] = {4, 3, 2, 1, 0, 8, 7, 6, 5};
    int test_array_len1 = sizeof(test_array1) / sizeof(test_array1[0]);
    radix_sort_with_sequence_storage(test_array1, test_array_len1, 1, -1);
    integer_array_println(
        "SeqStorageRadixSoredArray:  ", test_array1, test_array_len1
    );


    int test_array2[] = {1, 23, 456, 7, 89, 123, 4, 56, 789};
    int test_array_len2 = sizeof(test_array2) / sizeof(test_array2[0]);
    radix_sort_with_sequence_storage(test_array2, test_array_len2, 3, -1);
    integer_array_println(
        "SeqStorageRadixSoredArray:  ", test_array2, test_array_len2
    );

    return 0;
}
