#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H_


#include <stdio.h>
#include <stdlib.h>


#define BIG_INTEGER_CREATE_ERROR \
    "BigIntCreateError: " \
    "Failed to allocate memory for the BigInt\n"


#define BIG_INTEGER_CAPACITY_ERROR \
    "BigIntCapacityError: " \
    "The allocated length of the BigInt " \
    "object is invalid\n"


#define BIG_INTEGER_REALLOC_ERROR \
    "BigIntReallocError: " \
    "Failed to reallocate memory for the BigInt\n"


#define BIG_INTEGER_DEEPCOPY_ERROR \
    "BigIntDeepCopyError: " \
    "Failed to deep copy for the BigInt\n"


#define BIG_INTEGER_COMPARE_ERROR \
    "BigIntCompareError: " \
    "The buffer for storing the comparison " \
    "results is invalid.\n"


#define BIG_INTEGER_CREATE_SRC_ERROR \
    "BigIntCreateSrcError: " \
    "Error in the source data used to construct " \
    "the BigInt object\n"


#define BIG_INTEGER_REALLOC_SRC_ERROR \
    "BigIntReallocSrcError: " \
    "Error in the source data used to reallocate " \
    "the BigInt object\n"

#define BIG_INTEGER_DATA_TYPE_ERROR \
    "BigIntDataTypeError: " \
    "This data is of non-numeric type\n"


#define BIG_INTEGER_ACCESS_EXCEPTION \
    "BigIntAccessException: " \
    "Check whether parameter `BigInt*` is valid ?\n"


#define BIG_INTEGER_CHAR_TYPE_EXCEPTIOPN \
    "BigIntCharTypeException: " \
    "Check whether parameter BigIntCharType is valid ?\n"


#define BIG_INTEGER_ZERO '0'

#define BIG_INTEGER_NINE '9'

#define BIG_INTEGER_BASE_TEN 10


typedef enum BigIntSignChar {
    BIG_INTEGER_POSITIVE_CHAR = '+',
    BIG_INTEGER_NEGATIVE_CHAR = '-'
} BigIntSignChar;


typedef enum BigIntSignFlag {
    BIG_INTEGER_IS_NEGATIVE = 1,
    BIG_INTEGER_IS_NOT_NEGATIVE = 0,
} BigIntSignFlag;


typedef unsigned char u_char; 


typedef struct BigInt {
    u_char* number;
    BigIntSignFlag sign_flag;
    int cap;
    int len;
} BigInt;


BigInt* BigInt_of_chars(u_char* s, int num_len);


int BigInt_destroy(BigInt** this);


int BigInt_display(BigInt* this);


BigInt* Bigint_deepcopy(BigInt* this);


int BigInt_is_negative(BigInt* this);


int BigInt_strip(BigInt* this);


int BigInt_has_same_sign(BigInt* this, BigInt* n);


int BigInt_set_sign(BigInt* this, BigIntSignChar flag);


int BigInt_reverse_sign(BigInt* this);


int BigInt_abs_compare(BigInt* a, BigInt* b, int* state);


int BigInt_abs_add(BigInt* this, BigInt* n);


int BigInt_abs_subtract(BigInt* this, BigInt* n);


int BigInt_abs_multiply(
    BigInt* this, BigInt* n, BigInt* result
);


int BigInt_abs_divide(BigInt* this, BigInt* n);


int BigInt_add(BigInt* this, BigInt* n);


int BigInt_subtract(BigInt* this, BigInt* n);


int BigInt_multiply(BigInt* this, BigInt* n);


int BigInt_divide(BigInt* this, BigInt* n);


BigInt* _BigInt_alloc(int cap, BigIntSignFlag flag);


int _BigInt_realloc(BigInt* n, int new_cap);


int _BigInt_relocate_drop(BigInt** src, BigInt* dest);


#endif /* ! BIG_INTEGER_H_ */
