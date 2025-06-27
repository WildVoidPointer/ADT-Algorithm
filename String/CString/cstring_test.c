#include "cstring.h"


int main() {

    CStringUnitType* units1 = "Hello, World";
    size_t units1_len = 12;

    CStringUnitType* units2 = "Hello, C";
    size_t units2_len = 8;

    CString* cstring1 = cstring_create(units1, units1_len);
    CString* cstring2 = cstring_create(units2, units2_len);

    cstring_display(cstring1);
    cstring_display(cstring2);

    printf("Length of cstring1: %lu\n", cstring_length(cstring1));

    CString* ectype = cstring_deepcopy(cstring1);

    cstring_display(ectype);

    printf("CString Compare Result: %d\n", cstring_compare(cstring1, cstring2, NULL));
    printf("CString Compare Result: %d\n", cstring_compare(cstring1, ectype, NULL));

    CString* substring = cstring_substring_split(cstring1, 0, 5);
    cstring_display(substring);

    CString* concated = cstring_concat(cstring1, cstring2);
    cstring_display(concated);


    CStringUnitType unit = 'C';
    size_t index = 0;

    cstring_search(cstring1, NULL, NULL, CSTRING_UNIT_SEARCH_MODE);

    cstring_search(cstring1, &unit, &index, CSTRING_UNIT_SEARCH_MODE);
    printf("The Unit index: %lu\n", index);

    cstring_search(cstring2, &unit, &index, CSTRING_UNIT_SEARCH_MODE);
    printf("The Unit index: %lu\n", index);

    index = 7;

    cstring_search(cstring1, &unit, &index, CSTRING_INDEX_SEARCH_MODE);
    printf("The Index unit: %c\n", unit);

    cstring_search(cstring2, &unit, &index, CSTRING_INDEX_SEARCH_MODE);
    printf("The Index unit: %c\n", unit);
    
    index = 100;
    cstring_search(ectype, &unit, &index, CSTRING_INDEX_SEARCH_MODE);

    cstring_violent_pattern_matching(concated, cstring2, &index);
    printf("The Unit index: %lu\n", index);

    cstring_clear(cstring1);
    cstring_display(cstring1);

    cstring_clean(&cstring1);
    cstring_clean(&cstring2);
    cstring_clean(&ectype);
    cstring_clean(&substring);
    cstring_clean(&concated);

    printf("After free, the pointer state: %p\n", cstring1);
    printf("After free, the pointer state: %p\n", cstring2);
    printf("After free, the pointer state: %p\n", ectype);
    printf("After free, the pointer state: %p\n", substring);
    printf("After free, the pointer state: %p\n", concated);

    CStringUnitType* pattern_cs = "ABABCABAB";
    CStringUnitType* matching_cs = "ABABDABACDABABCABAB";

    CString* pattern_s = cstring_create(pattern_cs, 9);

    CString* wait_matching = cstring_create(matching_cs, 19);

    cstring_display(wait_matching);

    size_t res;

    cstring_kmp_matching(wait_matching, pattern_s, &res);

    printf("%lu \n", res);

    cstring_clean(&pattern_s);
    cstring_clean(&wait_matching);

    return 0;
}