#include <stdio.h>

#define MAX_LEN 1000010 

int EFFECTIVE_LEN;
int GLOBAL_ARRAY[MAX_LEN];

void quickSorter(int array[], int leftPtr, int rightPtr) {
    if (leftPtr >= rightPtr) 
        return;
    
    int medianPtr = (leftPtr + rightPtr) / 2;
    int medianValue = array[medianPtr];
    int tLeftPtr = leftPtr;
    int tRightPtr = rightPtr;

    while (tLeftPtr <= tRightPtr) {
        while (array[tLeftPtr] < medianValue) {
            tLeftPtr++;
        }
        while (array[tRightPtr] > medianValue) {
            tRightPtr--;
        }
        if (tLeftPtr <= tRightPtr) {
            int temp = array[tLeftPtr];
            array[tLeftPtr] = array[tRightPtr];
            array[tRightPtr] = temp;
            tLeftPtr++;
            tRightPtr--;
        }
    }
    quickSorter(array, leftPtr, tRightPtr);
    quickSorter(array, tLeftPtr, rightPtr);

}

int main()
{
    scanf("%d",&EFFECTIVE_LEN);
    
    for(int i = 0 ; i < EFFECTIVE_LEN ; i++)
    {
        scanf("%d",&GLOBAL_ARRAY[i]);
    }
    
    quickSorter(GLOBAL_ARRAY , 0 , EFFECTIVE_LEN-1);
    
    for(int i = 0 ; i < EFFECTIVE_LEN ; i++)
    {
        printf("%d ", GLOBAL_ARRAY[i]); 
    }
    
    return 0;
}

