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
    SequentialUnionFindSetUnit_display(find_res);


    SequentialUnionFindSetUnit* unit_root1 = &(suf_set_from_arr->units[3]);
    SequentialUnionFindSetUnit* unit_root2 = &(suf_set_from_arr->units[5]);
    SequentialUnionFindSet_root_union(unit_root1, unit_root2);
    SequentialUnionFindSet_display(suf_set_from_arr);
}
