#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<stdbool.h>


void quickSorter(char string[], int leftPtr, int rightPtr){
	if (leftPtr >= rightPtr) 
		return;
	int medianPtr = (leftPtr + rightPtr) / 2;
	char medianValue = string[medianPtr];
	int tLeftPtr = leftPtr - 1;
	int tRightPtr = rightPtr + 1;
	while (tLeftPtr < tRightPtr) {
		do tLeftPtr++; while(string[tLeftPtr] < medianValue);
		do tRightPtr--; while(string[tRightPtr] > medianValue);
		if (tLeftPtr < tRightPtr) {
			string[tLeftPtr] ^= string[tRightPtr];
			string[tRightPtr] ^= string[tLeftPtr];
			string[tLeftPtr] ^= string[tRightPtr];
		}
	}
	quickSorter(string, leftPtr, tRightPtr);
	quickSorter(string, tRightPtr+1, rightPtr);
}


bool isTranspositionString(const char* string1, const char* string2) {
    int len1 = strlen(string1);
    int len2 = strlen(string2);
    if (len1 != len2)
        return false;

    char* sortedString1 = strdup(string1);
    char* sortedString2 = strdup(string2);

    quickSorter(sortedString1, 0, len1 - 1);
    quickSorter(sortedString2, 0, len2 - 1);

    bool result = (strcmp(sortedString1, sortedString2) == 0);

    free(sortedString1);
    free(sortedString2);

    return result;
}

int main() {
    printf("%d\n", isTranspositionString("python", "thpyon"));
    printf("%d\n", isTranspositionString("cpp1", "ppc2"));
    return 0;
}
