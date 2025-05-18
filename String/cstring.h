#ifndef C_STRING_H
#define C_STRING_H

#ifdef __linux__
    #include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h> 


typedef int (*CStringComparator)(CString* cstring1, CString* cstring2);

typedef char CStringUnitType;


typedef struct CString {
    CStringUnitType* data;
    size_t length;
} CString;


int cstring_is_empty(CString* cstring);

int cstring_length(CString* cstring);

int cstring_compare(CString* cstring1, CString* cstring2, CStringComparator* comparator);

CString* cstring_create(CStringUnitType* units, size_t length);

CString* cstring_deepcopy(CString* cstring);

CString* cstring_substring_split(CString* cstring, size_t start, size_t end);

CString* cstring_concat(CString* cstring1, CString* cstring2);

CString* cstring_unit_search(CString* cstring, CStringUnitType* unit);

CString* cstring_clear(CString* cstring);

CString* cstring_clean(CString** cstring);

#endif