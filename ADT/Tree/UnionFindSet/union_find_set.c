#include "union_find_set.h"


SequentialUnionFindSet* SequentialUnionFindSet_create(size_t size) {
    SequentialUnionFindSet* suf_set = (SequentialUnionFindSet*) malloc (
        sizeof(SequentialUnionFindSet)
    );
    if (suf_set == NULL) {
        fprintf(stderr, UNION_FIND_SET_CREATE_ERROR);
        return NULL;
    }

    suf_set->units = (SequentialUnionFindSetUnit*) malloc (
        sizeof(SequentialUnionFindSetUnit) * size
    );
    if (suf_set->units == NULL) {
        fprintf(stderr, UNION_FIND_SET_CREATE_ERROR);
        SequentialUnionFindSet_destroy(&suf_set);
        return NULL;
    }

    suf_set->size = size;
    return suf_set;
}


int SequentialUnionFindSet_destroy(SequentialUnionFindSet** suf_set) {
    if (suf_set == NULL || *suf_set == NULL) {
        fprintf(stderr, UNION_FIND_SET_ACCESS_EXCEPTION);
        return -1;
    }

    if ((*suf_set)->units != NULL) {
        free((*suf_set)->units);
    }
    free(*suf_set);
    *suf_set = NULL;
    return 0;
}


int SequentialUnionFindSet_display(SequentialUnionFindSet* suf_set) {
    if (suf_set == NULL) {
        fprintf(stderr, UNION_FIND_SET_BUILD_SRC_ACCESS_EXCEPTION);
        return -1;
    }

    fputs("SequentialUnionFindSet: {  ", stdout);
    for (size_t i = 0; i < suf_set->size; i++) {
        printf(
            "%d:%d:%lu  ", 
            suf_set->units[i].parent_idx, 
            suf_set->units[i].val,
            suf_set->units[i].ele_num
        );
    }
    fputs("}\n", stdout);

    return 0;
}


SequentialUnionFindSet* SequentialUnionFindSet_build_of_array(
    UnionFindSetDataType arr[], size_t len
) {
    if (arr == NULL) {
        fprintf(stderr, UNION_FIND_SET_BUILD_SRC_ACCESS_EXCEPTION);
        return NULL;
    }

    SequentialUnionFindSet* suf_set = SequentialUnionFindSet_create(len);
    if (suf_set == NULL) {
        fprintf(stderr, UNION_FIND_SET_BUILD_ERROR);
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        suf_set->units[i].parent_idx = -1;
        suf_set->units[i].val = arr[i];
        suf_set->units[i].ele_num = 1;
        suf_set->units[i].self_idx = i;
    }

    return suf_set;
}


SequentialUnionFindSetUnit* SequentialUnionFindSet_root_find(
    SequentialUnionFindSet* suf_set, SequentialUnionFindSetUnit* ele
) {
    if (suf_set == NULL || ele == NULL) {
        fprintf(stderr, UNION_FIND_SET_ACCESS_EXCEPTION);
        return NULL;
    }

    while (ele->parent_idx > 0) {
        ele = &(suf_set->units[ele->parent_idx]);
    }

    return ele;
}


int SequentialUnionFindSet_root_union(
    SequentialUnionFindSetUnit* root1, SequentialUnionFindSetUnit* root2,
    UnionFindSetUnionCompareModeEnum mode
) {
    if (root1 == NULL || root2 == NULL) {
        fprintf(stderr, UNION_FIND_SET_UNION_SRC_ACCESS_EXCEPTION);
        return -1;
    }

    if (root1 == root2) {
        return 0;
    }

    if (mode == UNION_FIND_SET_UNION_COMPARE_DISABLE) {
        root2->parent_idx = root1->self_idx;
        root1->ele_num += root2->ele_num;
    } else if (mode == UNION_FIND_SET_UNION_COMPARE_ENABLE) {
        if (root1->ele_num >= root2->ele_num) {
            root2->parent_idx = root1->self_idx;
            root1->ele_num += root2->ele_num;
        } else {
            root1->parent_idx = root2->self_idx;
            root2->ele_num += root1->ele_num;
        }
    } else {
        
    }
    
    return 0;
}


int SequentialUnionFindSetUnit_level_compress(
    SequentialUnionFindSet* suf_set, SequentialUnionFindSetUnit* suf_unit
) {
    if (suf_set == NULL || suf_unit == NULL) {
        fprintf(stderr, UNION_FIND_SET_FINDING_EXCEPTION);
        return -1;
    }

    SequentialUnionFindSetUnit* suf_unit_root = suf_unit;

    while (suf_unit_root->parent_idx >= 0) {
        suf_unit_root = &(suf_set->units[suf_unit_root->parent_idx]);
    }

    SequentialUnionFindSetUnit* suf_unit_curr_parent;

    size_t curr_decrease = 1;

    while (suf_unit != suf_unit_root) {
        suf_unit_curr_parent = &(suf_set->units[suf_unit->parent_idx]);
        suf_unit->parent_idx = suf_unit_root->self_idx;

        if (suf_unit_curr_parent != suf_unit_root) {
            suf_unit_curr_parent->ele_num -= curr_decrease;
            curr_decrease++;
        }
        
        suf_unit = suf_unit_curr_parent;
    }

    return 0;
}


int SequentialUnionFindSetUnit_display(
    SequentialUnionFindSetUnit* suf_unit
) {

    if (suf_unit == NULL) {
        fprintf(stderr, UNION_FIND_SET_UNIT_ACCESS_EXCEPTION);
        return -1;
    }

    printf(
        "SequentialUnionFindSetUnit: "  \
        "{  parent_idx: %d, val: %d, ele_num: %lu  }\n",
        suf_unit->parent_idx,
        suf_unit->val,
        suf_unit->ele_num
    );

    return 0;
}
