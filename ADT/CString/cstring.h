#ifndef C_STRING_H_
#define C_STRING_H_

#ifdef __linux__
    #include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h>


#define CSTRING_ACCESS_ERROR \
    "CStringAccessError: " \
    "The data address of the CString cannot be accessed\n"


#define CSTRING_UNITS_ACCESS_ERROR \
    "CStringUnitsAccessError: " \
    "The data address of the CString->units cannot be accessed\n"


#define CSTRING_UNIT_ACCESS_ERROR \
    "CStringUnitAccessError: " \
    "The data address of the CStringUnit cannot be accessed\n"


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


#define CSTRING_PMT_INIT_ERROR \
    "CStringPMTinitError: Memory initialization of CStringPMT failed\n"


#define CSTRING_PMT_UNIT_INIT_ERROR \
    "CStringPMTunitInitError: " \
    "Memory initialization of CStringPMTunit failed\n"


#define CSTRING_PMT_ACCESS_ERROR \
    "CStringPMTaccessError: " \
    "The data address of the CStringPMT cannot be accessed\n"



typedef enum CStringSearchModeEnum {
    CSTRING_UNIT_SEARCH_MODE,
    CSTRING_INDEX_SEARCH_MODE
} CStringSearchModeEnum;


typedef char CStringUnitType;


typedef struct CString {
    CStringUnitType* data;
    size_t length;
} CString;


typedef size_t PMTunitType;

typedef struct CStringPMT {
    PMTunitType* table;
    size_t length;
} CStringPMT;


typedef int (*CStringComparator)(
    CString* cstring1, CString* cstring2
);


int CString_is_empty(CString* cstring);

int CString_is_valid(CString* cstring);

size_t CString_length(CString* cstring);

CString* CString_create(CStringUnitType* units, size_t length);

int CString_compare(
    CString* cstring1, CString* cstring2, 
    CStringComparator comparator
);

CString* CString_deepcopy(CString* cstring);

CString* CString_split(
    CString* cstring, size_t start, size_t offset
);

CString* CString_concat(CString* cstring1, CString* cstring2);

int CString_search(
    CString* cstring, CStringUnitType* unit, 
    size_t* index, CStringSearchModeEnum mode
);

int CString_violent_matching(
    CString* cstring1, CString* cstring2, size_t* pos
);

CStringPMT* CStringPMT_build(CString* s);

int CString_kmp_matching(
    CString* cstring, CString* pattern, size_t* res
);

int CString_clear(CString* cstring);

int CString_display(CString* cstring);

int _CString_unit_destroy(CStringUnitType** unit);

int CString_destroy(CString** cstring);

int CStringPMT_destroy(CStringPMT** pmt);

#endif
