#include "cstring.h"

#ifdef __linux__
    #include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h>


int cstring_is_valid(CString* cstring) {
    return (cstring == NULL || cstring->data == NULL) ? 0 : 1;
}


int cstring_is_empty(CString* cstring) {
    return (cstring_is_valid(cstring)) ? cstring->length == 0 : -1;
}


size_t cstring_length(CString* cstring) {
    return (cstring_is_valid(cstring)) ? cstring->length : -1;
}


CString* cstring_create(CStringUnitType* units, size_t length) {

    if (units == NULL) {
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

    if (!cstring_is_valid(cstring)) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return NULL;
    }

    CString* ectype = cstring_create(cstring->data, cstring->length);

    if (!cstring_is_valid(ectype)) {
        fprintf(stderr, CSTRING_DEEPCOPY_ERROR);
        return NULL;
    }

    return ectype;
}


int cstring_compare(
    CString* cstring1, CString* cstring2, CStringComparator comparator) {

    if (!cstring_is_valid(cstring1) || !cstring_is_valid(cstring2)) {
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


CString* cstring_substring_split(CString* cstring, size_t start, size_t offset) {

    if (!cstring_is_valid(cstring) || start > cstring->length || 
            offset > cstring->length || start > offset) {

        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return NULL;
    }

    CString* subcstring = (CString*) malloc (sizeof(CString));

    if (subcstring == NULL) {
        fprintf(stderr, CSTRING_INIT_ERROR);
        return NULL;
    }

    subcstring->data = (CStringUnitType*) malloc (sizeof(CStringUnitType) * offset);

    if (subcstring == NULL) {
        fprintf(stderr, CSTRING_UNITS_INIT_ERROR);
        free(subcstring);
        return NULL;
    }

    for (size_t i = 0; i < offset; i++) {
        subcstring->data[i] = cstring->data[start + i];
    }

    return subcstring;
}


CString* cstring_concat(CString* cstring1, CString* cstring2) {

    if (!cstring_is_valid(cstring1) || !cstring_is_valid(cstring2)) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return NULL;
    }

    CString* concated = (CString*) malloc (sizeof(CString));

    if (concated == NULL) {
        fprintf(stderr, CSTRING_INIT_ERROR);
        return NULL;
    }

    concated->data = (CStringUnitType*) malloc (sizeof(CStringUnitType) * cstring1->length + cstring2->length);

    if (concated->data == NULL) {
        fprintf(stderr, CSTRING_UNITS_INIT_ERROR);
        return NULL;
    }

    size_t concated_offset = 0;

    for (size_t i = 0; i < cstring1->length; i++) {
        concated->data[concated_offset++] = cstring1->data[i];
    }

    for (size_t i = 0; i < cstring2->length; i++) {
        concated->data[concated_offset++] = cstring2->data[i];
    }
}
