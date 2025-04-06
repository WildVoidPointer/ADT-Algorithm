#include <stdio.h>


int array_section_search(int left, int right, int sl[], int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (sl[mid] == target) {
            return 1;
        }
        else if (sl[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return 0;
}


void 
search_existential_elements_in_sls1(int size, int sl1[], int sl2[], int sl3[]){
    int elements[size];
    int index = 0;
    for (int i = 0; i < size; i++) {
        int sl2_has = array_section_search(0, size, sl2, sl1[i]);
        int sl3_has = array_section_search(0, size, sl3, sl1[i]);
        if (sl2_has && sl3_has){
            elements[index++] = sl1[i];
        }
    }
}


void 
search_existential_elements_in_sls2(int size, int sl1[], int sl2[], int sl3[]) {
    int elements[size];
    int index = 0;

    int i = 0, j = 0, k = 0;

    while (i < size && j < size && k < size) {
        if (sl1[i] == sl2[j] && sl2[j] == sl3[k]) {
            elements[index++] = sl1[i];
            i++; j++; k++;
        } 
        else if (sl1[i] < sl2[j]) {
            i++;
        } 
        else if (sl2[j] < sl3[k]) {
            j++;
        } 
        else {
            k++;
        }
    }
}
