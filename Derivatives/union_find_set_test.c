#include "union_find_set.h"


int main() {
    int test_array1[] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
    int test_array_len1 = sizeof(test_array1) / sizeof(test_array1[0]);


    SequentialUnionFindSet* suf_set_from_arr = 
        SequentialUnionFindSet_build_of_array(test_array1, test_array_len1);

    SequentialUnionFindSet_display(suf_set_from_arr);


    SequentialUnionFindSetUnit unit_search_target = {
        .parent_idx = 3,
        .ele_num = 0,
        .val = 5
    };
    SequentialUnionFindSetUnit* find_res = SequentialUnionFindSet_root_find(
        suf_set_from_arr, &unit_search_target
    );
    printf("SequentialUnionFindSet RootFindResult >>>>  ");
    SequentialUnionFindSetUnit_display(find_res);


    for (size_t i = test_array_len1 - 1; i >= 1; i--) {
        SequentialUnionFindSetUnit* unit_root1 = &(suf_set_from_arr->units[i - 1]);
        SequentialUnionFindSetUnit* unit_root2 = &(suf_set_from_arr->units[i]);
        SequentialUnionFindSet_root_union(
            unit_root1, unit_root2, UNION_FIND_SET_UNION_COMPARE_DISABLE
        );
    }
    SequentialUnionFindSet_display(suf_set_from_arr);


    SequentialUnionFindSetUnit* unit_bottom = 
        &(suf_set_from_arr->units[test_array_len1 - 1]);

    SequentialUnionFindSetUnit_display(unit_bottom);
    SequentialUnionFindSetUnit_level_compress(suf_set_from_arr, unit_bottom);
    SequentialUnionFindSet_display(suf_set_from_arr);
}
