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
    "CStringUnitsAccessError: The data address of the CString->units cannot be accessed\n"

#define CSTRING_UNIT_ACCESS_ERROR \
    "CStringUnitAccessError: The data address of the CStringUnit cannot be accessed\n"

#define CSTRING_INIT_ERROR \
    "CStringInitError: Memory initialization of CString failed\n"

#define CSTRING_UNITS_INIT_ERROR \
    "CStringUnitsInitError: Memory initialization of CStringUnits failed\n"

#define CSTRING_DEEPCOPY_ERROR \
    "CStringDeepCopyError: The copy of the cstring object failed\n"

#define CSTRING_SEARCH_INDEX_ERROR \
    "CstringSearchIndexError: Index out of range for CString\n"

#define CSTRING_SEARCH_BUFFER_ERROR \
    "CStringSearchBufferError: The search buffer of CString cannot be accessed\n"

#define CSTRING_SEARCH_MODE_ERROR \
    "CStringSearchModeError: The CString search pattern is invalid\n"

#define PMT_INIT_ERROR \
    "PMTinitError: Memory initialization of PMT failed\n"

#define PMT_UNIT_INIT_ERROR \
    "PMTunitInitError: Memory initialization of PMTunit failed\n"

#define PMT_ACCESS_ERROR \
    "PMTaccessError: The data address of the PMT cannot be accessed\n"


#define CSTRING_UNIT_SEARCH_MODE 0

#define CSTRING_INDEX_SEARCH_MODE 1


typedef char CStringUnitType;


typedef int CStringSearchMode;


typedef struct CString {
    CStringUnitType* data;
    size_t length;
} CString;


typedef size_t PMTunitType;

typedef struct PMT {
    PMTunitType* table;
    size_t length;
} PMT;


typedef int (*CStringComparator)(CString* cstring1, CString* cstring2);


int cstring_is_empty(CString* cstring);

int cstring_is_valid(CString* cstring);

size_t cstring_length(CString* cstring);

CString* cstring_create(CStringUnitType* units, size_t length);

int cstring_compare(CString* cstring1, CString* cstring2, CStringComparator comparator);

CString* cstring_deepcopy(CString* cstring);

CString* cstring_substring_split(CString* cstring, size_t start, size_t offset);

CString* cstring_concat(CString* cstring1, CString* cstring2);

int cstring_search(
    CString* cstring, CStringUnitType* unit, size_t* index, CStringSearchMode mode);

int cstring_violent_pattern_matching(CString* cstring1, CString* cstring2, size_t* pos);

PMT* cstring_build_partial_match_table(CString* s);

int cstring_kmp_matching(CString* cstring, CString* pattern, size_t* res);

int cstring_clear(CString* cstring);

int cstring_display(CString* cstring);

int _cstring_unit_clean(CStringUnitType** unit);

int cstring_clean(CString** cstring);

int pmt_clean(PMT** pmt);

#endif
