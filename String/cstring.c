#include "cstring.h"

#ifdef __linux__
    #include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h>


int cstring_is_empty(CString* cstring) {
    return (cstring != NULL) ? cstring->length == 0 : -1;
}


size_t cstring_length(CString* cstring) {
    return (cstring != NULL) ? cstring->length : -1;
}


CString* cstring_create(CStringUnitType* units, size_t length) {

    if (units == NULL || length < 0) {
        fprintf(stderr, CSTRING_UNITS_ACCESS_ERROR);
        return NULL;
    }

    CString* cstring = (CString*) malloc (sizeof(CString));

    if (cstring == NULL) {
        fprintf(stderr, CSTRING_INIT_ERROR);
        return NULL;
    }

    cstring->data = (CStringUnitType*) malloc (sizeof(CStringUnitType) * length);

    if (cstring->data == NULL) {
        fprintf(stderr, CSTRING_UNITS_INIT_ERROR);
        free(cstring);
        return NULL;
    }

    for(size_t i = 0; i < length; i++) {
        cstring->data[i] = units[i];
    }

    cstring->length = length;

    return cstring;
}


CString* cstring_deepcopy(CString* cstring) {
    if (cstring == NULL) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return NULL;
    }
}


int cstring_compare(
    CString* cstring1, CString* cstring2, CStringComparator comparator) {

    if (cstring1 == NULL || cstring2 == NULL) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return -1;
    }

    if (comparator != NULL) {
        return comparator(cstring1, cstring2);
    }

    size_t min_iter = (cstring1->length > cstring2->length) ? 
                            cstring2->length : cstring1->length;

    int compare_res = 0;
    
    for (size_t i = 0; i < min_iter; i++) {
        if (cstring1->data[i] > cstring2->data[i]) {
            compare_res = 1;
            break;
        } else if (cstring1->data[i] < cstring2->data[i]) {
            compare_res = -1;
            break;
        }
    }

    return compare_res;
}
