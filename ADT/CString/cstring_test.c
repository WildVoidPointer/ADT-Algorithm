#include "cstring.h"


int main() {

    CStringUnitType* units1 = "Hello, World";
    size_t units1_len = 12;

    CStringUnitType* units2 = "Hello, C";
    size_t units2_len = 8;

    CString* cstring1 = CString_create(units1, units1_len);
    CString* cstring2 = CString_create(units2, units2_len);

    CString_display(cstring1);
    CString_display(cstring2);

    printf("Length of cstring1: %lu\n", CString_length(cstring1));

    CString* ectype = CString_deepcopy(cstring1);

    CString_display(ectype);

    printf(
        "CString Compare Result: %d\n", 
        CString_compare(cstring1, cstring2, NULL)
    );
    printf(
        "CString Compare Result: %d\n", 
        CString_compare(cstring1, ectype, NULL)
    );

    CString* substring = CString_split(cstring1, 0, 5);
    CString_display(substring);

    CString* concated = CString_concat(cstring1, cstring2);
    CString_display(concated);


    CStringUnitType unit = 'C';
    size_t index = 0;

    CString_search(cstring1, NULL, NULL, CSTRING_UNIT_SEARCH_MODE);

    CString_search(cstring1, &unit, &index, CSTRING_UNIT_SEARCH_MODE);
    printf("The Unit index: %lu\n", index);

    CString_search(cstring2, &unit, &index, CSTRING_UNIT_SEARCH_MODE);
    printf("The Unit index: %lu\n", index);

    index = 7;

    CString_search(cstring1, &unit, &index, CSTRING_INDEX_SEARCH_MODE);
    printf("The Index unit: %c\n", unit);

    CString_search(cstring2, &unit, &index, CSTRING_INDEX_SEARCH_MODE);
    printf("The Index unit: %c\n", unit);
    
    index = 100;
    CString_search(ectype, &unit, &index, CSTRING_INDEX_SEARCH_MODE);

    CString_violent_matching(concated, cstring2, &index);
    printf("The Unit index: %lu\n", index);

    CString_clear(cstring1);
    CString_display(cstring1);

    CString_destroy(&cstring1);
    CString_destroy(&cstring2);
    CString_destroy(&ectype);
    CString_destroy(&substring);
    CString_destroy(&concated);

    printf("After free, the pointer state: %p\n", cstring1);
    printf("After free, the pointer state: %p\n", cstring2);
    printf("After free, the pointer state: %p\n", ectype);
    printf("After free, the pointer state: %p\n", substring);
    printf("After free, the pointer state: %p\n", concated);

    CStringUnitType* pattern_cs = "ABABCABAB";
    CStringUnitType* matching_cs = "ABABDABACDABABCABAB";

    CString* pattern_s = CString_create(pattern_cs, 9);

    CString* wait_matching = CString_create(matching_cs, 19);

    CString_display(wait_matching);

    size_t res;

    CString_kmp_matching(wait_matching, pattern_s, &res);

    printf("%lu \n", res);

    CString_destroy(&pattern_s);
    CString_destroy(&wait_matching);

    return 0;
}