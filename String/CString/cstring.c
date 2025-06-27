#include "cstring.h"

#ifdef __linux__
    #include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h>


int cstring_is_valid(CString* cstring) {
    return (cstring == NULL) ? 0 : 1;
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

    subcstring->length = offset;

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

    concated->data = (CStringUnitType*) malloc 
            (sizeof(CStringUnitType) * cstring1->length + cstring2->length);

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

    concated->length = concated_offset;

    return concated;
}


int cstring_violent_pattern_matching(CString* cstring1, CString* cstring2, size_t* pos) {
    if (! cstring_is_valid(cstring1) || ! cstring_is_valid(cstring2)) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return -1;
    }

    if (pos == NULL) {
        fprintf(stderr, CSTRING_SEARCH_BUFFER_ERROR);
        return -1;
    }

    size_t cstring1_offset = 0;
    size_t cstring2_offset = 0;

    while (cstring1_offset < cstring1->length && cstring2_offset < cstring2->length) {
        if (cstring1->data[cstring1_offset] == cstring2->data[cstring2_offset]) {
            cstring1_offset++;
            cstring2_offset++;
        } else {
            cstring1_offset = cstring1_offset - cstring2_offset + 1;
            cstring2_offset = 0;
        }
    }

    if (cstring2_offset == cstring2->length) {
        *pos = cstring1_offset - cstring2->length;
        return 0;
    } else {
        return -1;
    }
}


int cstring_search(
    CString* cstring, CStringUnitType* unit, size_t* index, CStringSearchMode mode) {

    if (!cstring_is_valid(cstring)) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return -1;
    }

    if (index == NULL || unit == NULL) {
        fprintf(stderr, CSTRING_SEARCH_BUFFER_ERROR);
        return -1;
    }

    if (mode == CSTRING_UNIT_SEARCH_MODE) {
        for (size_t i = 0; i < cstring->length; i++) {
            if (cstring->data[i] == *unit) {
                *index = i;
                break;
            }
        }

    } else if (mode == CSTRING_INDEX_SEARCH_MODE) {
        if ((*index) > cstring->length) {
            fprintf(stderr, CSTRING_SEARCH_INDEX_ERROR);
            return -1;
        }

        *unit = cstring->data[(*index)];
    } else {
        fprintf(stderr, CSTRING_SEARCH_MODE_ERROR);
        return -1;
    }

    return 0;
}


PMT* cstring_build_partial_match_table(CString* s) {
    PMT* pmt = (PMT*) malloc (sizeof(PMT));
    if (pmt == NULL) {
        fprintf(stderr, PMT_INIT_ERROR);
        return NULL;
    }

    pmt->table = (PMTunitType*) malloc(s->length * sizeof(PMTunitType));

    if (pmt->table == NULL) {
        fprintf(stderr, PMT_UNIT_INIT_ERROR);
        return NULL;
    }

    pmt->length = s->length;

    pmt->table[0] = 0;

    int prev_pmt_v = 0;

    size_t i = 1;

    while (i < s->length) {
        if (s->data[i] == s->data[prev_pmt_v]) {
            prev_pmt_v++;
            pmt->table[i] = prev_pmt_v;
            i++;
        } else {
            if (prev_pmt_v != 0) {
                prev_pmt_v = pmt->table[prev_pmt_v - 1];
            } else {
                pmt->table[i] = 0;
                i++;
            }
        }
    }

    return pmt;
}


int cstring_kmp_matching(CString* cstring, CString* pattern, size_t* res) {
    if (cstring == NULL || pattern == NULL) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return -1;
    }

    if (res == NULL) {
        fprintf(stderr, CSTRING_SEARCH_BUFFER_ERROR);
        return -1;
    }

    PMT* pmt = cstring_build_partial_match_table(pattern);

    size_t cstring_offset = 0;
    size_t pattern_i = 0;

    while (cstring_offset < cstring->length) {
        if (cstring->data[cstring_offset] == pattern->data[pattern_i]) {
            cstring_offset++;
            pattern_i++;

            if (pattern_i == pattern->length){
                *res = cstring_offset - pattern_i;
                break;
            }
        } else {
            if (pattern_i != 0) {
                pattern_i = pmt->table[pattern_i - 1];
            } else {
                cstring_offset++;
            }
        }
    }

    pmt_clean(&pmt);
    return 0;
}


int cstring_clear(CString* cstring) {
    if (!cstring_is_valid(cstring)) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return -1;
    }

    free(cstring->data);

    cstring->data = NULL;

    cstring->length = 0;

    return 0;
}


int cstring_display(CString* cstring) {
    if (!cstring_is_valid(cstring)) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return -1;
    }

    printf("CStringObject.{ data : \"");
    for (size_t i = 0; i < cstring->length; i++) {
        printf("%c", cstring->data[i]);
    }
    printf("\", length: %lu }\n", cstring->length);

    return 0;
}


int _cstring_unit_clean(CStringUnitType** unit) {
    if (unit == NULL || *unit == NULL) {
        fprintf(stderr, CSTRING_UNIT_ACCESS_ERROR);
        return -1;
    }

    free((*unit));

    *unit = NULL;

    return 0;
}


int cstring_clean(CString** cstring) {
    if (cstring == NULL || !cstring_is_valid(*cstring)) {
        fprintf(stderr, CSTRING_ACCESS_ERROR);
        return -1;
    }

    free((*cstring)->data);
    free(*cstring);

    *cstring = NULL;

    return 0;
}


int pmt_clean(PMT** pmt) {
    if (pmt == NULL || *pmt == NULL) {
        fprintf(stderr, PMT_ACCESS_ERROR);
        return -1;
    }

    free((*pmt)->table);
    free((*pmt));
    *pmt = NULL;
    return 0;
}
