#ifndef C_STRING_H
#define C_STRING_H

#ifdef __linux__
    #include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h> 


#define CSTRING_ACCESS_ERROR \
    "CStringAccessError: The data address of the CString cannot be accessed\n"

#define CSTRING_UNITS_ACCESS_ERROR \
    "CStringUnitsAccessError: The data address of the CStringUnits cannot be accessed\n"

#define CSTRING_INIT_ERROR \
    "CStringInitError: Memory initialization of CString failed\n"

#define CSTRING_UNITS_INIT_ERROR \
    "CStringUnitsInitError: Memory initialization of CStringUnits failed\n"

#define CSTRING_DEEPCOPY_ERROR \
    "CStringDeepCopyError: The copy of the cstring object failed\n"


typedef int (*CStringComparator)(CString* cstring1, CString* cstring2);

typedef char CStringUnitType;


typedef struct CString {
    CStringUnitType* data;
    size_t length;
} CString;


int cstring_is_empty(CString* cstring);

int cstring_is_valid(CString* cstring);

size_t cstring_length(CString* cstring);

CString* cstring_create(CStringUnitType* units, size_t length);

int cstring_compare(CString* cstring1, CString* cstring2, CStringComparator comparator);

CString* cstring_deepcopy(CString* cstring);

CString* cstring_substring_split(CString* cstring, size_t start, size_t end);

CString* cstring_concat(CString* cstring1, CString* cstring2);

CString* cstring_unit_search(CString* cstring, CStringUnitType* unit);

CString* cstring_clear(CString* cstring);

CString* cstring_clean(CString** cstring);

#endif