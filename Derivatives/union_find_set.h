#ifndef UNION_FIND_SET_H_
#define UNION_FIND_SET_H_


#include <stdio.h>
#include <stdlib.h>


#ifdef __linux__
    #include <sys/types.h>
#endif


#define UNION_FIND_SET_CREATE_ERROR \
    "UnionFindSetCreateError: " \
    "Memory initialization of UnionFindSet failed\n"


#define UNION_FIND_SET_BUILD_ERROR \
    "UnionFindSetBuildError: " \
    "Memory initialization failed in process of building UnionFindSet\n"


#define UNION_FIND_SET_UNIT_CREATE_ERROR \
    "UnionFindSetUnitCreateError: " \
    "Memory initialization of UnionFindSetUnit failed\n"


#define UNION_FIND_SET_ACCESS_EXCEPTION \
    "UnionFindSetAccessException: " \
    "The data address of the UnionFindSet cannot be accessed\n"


#define UNION_FIND_SET_BUILD_SRC_ACCESS_EXCEPTION \
    "UnionFindSetBuildSrcAccessException: " \
    "The data address of the UnionFindSet cannot be accessed\n"


#define UNION_FIND_SET_UNIT_UNION_EXCEPTION \
    "UnionFindSetUnitUnionException: " \
    "The data address of the UnionFindSetUnit cannot be accessed\n"


#define UNION_FIND_SET_UNIT_ACCESS_EXCEPTION \
    "UnionFindSetUnitAccessException: " \
    "The data address of the UnionFindSetUnit cannot be accessed\n"


typedef int UnionFindSetDataType;


typedef struct SequentialUnionFindSetUnit {
    UnionFindSetDataType val;
    int parent_idx;
    size_t ele_num;
    size_t self_idx;
} SequentialUnionFindSetUnit;


typedef struct LinkedUnionFindSetUnit {
    UnionFindSetDataType val;
    struct LinkedUnionFindSetUnit* parent;
    size_t size;
} LinkedUnionFindSetUnit;


typedef struct SequentialUnionFindSet {
    SequentialUnionFindSetUnit* units;
    size_t size;
} SequentialUnionFindSet;


SequentialUnionFindSet* SequentialUnionFindSet_create(size_t size);


int SequentialUnionFindSet_clean(SequentialUnionFindSet** suf_set);


int SequentialUnionFindSet_display(SequentialUnionFindSet* suf_set);


SequentialUnionFindSet* SequentialUnionFindSet_build_of_array(
    UnionFindSetDataType arr[], size_t len
);


SequentialUnionFindSetUnit* SequentialUnionFindSet_root_find(
    SequentialUnionFindSet* suf_set, SequentialUnionFindSetUnit* ele
);


int SequentialUnionFindSet_root_union(
    SequentialUnionFindSetUnit* root1, SequentialUnionFindSetUnit* root2
);


int SequentialUnionFindSetUnit_display(SequentialUnionFindSetUnit* suf_unit);


#endif
