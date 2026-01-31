#include "big_integer.h"
#include <stdio.h>
#include <stdlib.h>


BigInt* BigInt_of_chars(u_char* s, int num_len) {

    if (s == NULL || num_len < 0) {
        fprintf(stderr, BIG_INTEGER_CREATE_SRC_ERROR);
        return NULL;
    }

    BigInt* n = (BigInt*) malloc (sizeof(BigInt));

    if (n == NULL) {
        fprintf(stderr, BIG_INTEGER_CREATE_ERROR);
        return NULL;
    }

    n->len = 0;

    int start = 0;

    if (s[0] == BIG_INTEGER_NEGATIVE_CHAR) {

        n->sign_flag = BIG_INTEGER_IS_NEGATIVE;
        start = 1;

    } else if (s[0] == BIG_INTEGER_POSITIVE_CHAR){

        n->sign_flag = BIG_INTEGER_IS_NOT_NEGATIVE;
        start = 1;

    } else if (
        BIG_INTEGER_ZERO <= s[0] && 
        s[0] <= BIG_INTEGER_NINE
    ) {

        n->sign_flag = BIG_INTEGER_IS_NOT_NEGATIVE;

    } else {
        fprintf(stderr, BIG_INTEGER_DATA_TYPE_ERROR);
        free(n);
        return NULL;
    }

    n->cap = num_len - start + 1;

    n->number = (u_char*) malloc (sizeof(u_char) * n->cap);

    n->number[n->cap - 1] = 0;

    if (n->number == NULL) {
        fprintf(stderr, BIG_INTEGER_CREATE_ERROR);
        free(n);
        return NULL;
    }

    for (int i = num_len - 1; i >= start; i--) {

        if (
            BIG_INTEGER_ZERO <= s[i] && 
            s[i] <= BIG_INTEGER_NINE
        ) {
            n->number[n->len++] = s[i] - BIG_INTEGER_ZERO;
        } else {
            fprintf(stderr, BIG_INTEGER_DATA_TYPE_ERROR);
            BigInt_destroy(&n);
            return NULL;
        }

    }

    BigInt_strip(n);

    return n;
}


int BigInt_destroy(BigInt** this) {

    if (this == NULL || (*this) == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }


    free((*this)->number);

    free(*this);

    *this = NULL;

    return 0;
}


int BigInt_display(BigInt* this) {

    if (this == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    printf("BigInt {  number: ");

    if (this->sign_flag == BIG_INTEGER_IS_NEGATIVE) {
        printf("%c", BIG_INTEGER_NEGATIVE_CHAR);
    }

    for (int i = this->len -1; i >= 0; i--) {
        printf("%c", this->number[i] + BIG_INTEGER_ZERO);
    }

    printf("  len: %d  cap: %d", this->len, this->cap);

    printf("  }\n");
}


BigInt* Bigint_deepcopy(BigInt* this) {
    
    if (this == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return NULL;
    }

    BigInt* copied = _BigInt_alloc(this->cap, this->sign_flag);

    if (copied == NULL) {
        fprintf(stderr, BIG_INTEGER_DEEPCOPY_ERROR);
        return NULL;
    }

    for (int i = 0; i < this->len; i++) {
        copied->number[copied->len++] = this->number[i];
    }

    return copied;
}


int BigInt_is_negative(BigInt* this) {
    return (
        this != NULL && 
        this->sign_flag == BIG_INTEGER_IS_NEGATIVE
    ) ? 1 : 0;
}


int BigInt_strip(BigInt* this) {

    if (this == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    while (
        this->len > 1 && 
        this->number[this->len - 1] == 0
    ) {
        this->len--;
    }

    return 0;
}


int BigInt_has_same_sign(BigInt* this, BigInt* n) {

    if (this == NULL || n == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    return this->sign_flag == n->sign_flag;
}


int BigInt_set_sign(BigInt* this, BigIntSignChar flag) {

    if (this == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    if (flag == BIG_INTEGER_IS_NEGATIVE) {
        this->sign_flag = BIG_INTEGER_IS_NEGATIVE;
    } else if (flag == BIG_INTEGER_IS_NOT_NEGATIVE) {
        this->sign_flag = BIG_INTEGER_IS_NOT_NEGATIVE;
    } else {
        fprintf(stderr, BIG_INTEGER_CHAR_TYPE_EXCEPTIOPN);
        return -1;
    }

    return 0;
}


int BigInt_reverse_sign(BigInt* this) {

    if (this == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    if (this->sign_flag == BIG_INTEGER_IS_NEGATIVE) {
        BigInt_set_sign(this, BIG_INTEGER_IS_NOT_NEGATIVE);
    } else {
        BigInt_set_sign(this, BIG_INTEGER_IS_NEGATIVE);
    }

    return 0;
}


int BigInt_abs_compare(BigInt* a, BigInt* b, int* state) {

    if (a == NULL || b == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    if (state == NULL) {
        fprintf(stderr, BIG_INTEGER_COMPARE_ERROR);
        return -1;
    }

    if (a->len != b->len) {
        *state = a->len - b->len;
        goto big_int_compare_end;
    }

    for (int i = a->len - 1; i >= 0; i--) {
        if (a->number[i] != b->number[i]) {
            *state = a->number[i] - b->number[i];
            goto big_int_compare_end;
        }
    }

big_int_compare_end:
    return 0;
}


int BigInt_abs_add(BigInt* this, BigInt* n) {

    if (this == NULL || n == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    int carry = 0;

    int max_len = (this->len > n->len) ? this->len : n->len;

    if (this->cap < n->len) {
        _BigInt_realloc(this, n->cap);
    }

    int new_len = 0;

    for (int i = 0; i < max_len || carry; i++) {

        int sum = carry;

        if (i < this->len) {
            sum = sum + this->number[i];
        }

        if (i < n->len) {
            sum = sum + n->number[i];
        }

        if (sum >= BIG_INTEGER_BASE_TEN) {
            carry = 1;
            sum = sum - BIG_INTEGER_BASE_TEN;
        } else {
            carry = 0;
        }

        this->number[new_len++] = sum;
    }

    this->len = new_len;

    return 0;
}


int BigInt_abs_subtract(BigInt* this, BigInt* n) {

    if (this == NULL || n == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    int borrow = 0;

    for (int i = 0; i < this->len; i++) {
        int diff = this->number[i] - borrow;

        if (i < n->len) {
            diff = diff - n->number[i];
        }

        if (diff < 0) {
            diff = diff + BIG_INTEGER_BASE_TEN;
            borrow = 1;
        } else {
            borrow = 0;
        }

        this->number[i] = diff;
    }

    return 0;
}


int BigInt_abs_multiply(
    BigInt* this, BigInt* n, BigInt* result
) {

    if (this == NULL || n == NULL || result == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    for (int i = 0; i < n->len; i++) {

        int carry = 0;

        for (int j = 0; j < this->len; j++) {

            int product = result->number[i + j] + 
                n->number[i] * this->number[j] + carry;

            result->number[i + j] = 
                product % BIG_INTEGER_BASE_TEN;

            carry = product / BIG_INTEGER_BASE_TEN;
        }

        int pos = i + this->len;

        while (carry) {

            result->number[pos] = result->number[pos] + 
                carry % BIG_INTEGER_BASE_TEN;

            carry = carry / BIG_INTEGER_BASE_TEN;

            pos++;
        }
    }

    return 0;
}


int BigInt_abs_divide(BigInt* this, BigInt* n);


int BigInt_add(BigInt* this, BigInt* n) {

    if (this->sign_flag != n->sign_flag) {
        return BigInt_subtract(this, n);
    } else {
        return BigInt_abs_add(this, n);
    }

}


int BigInt_subtract(BigInt* this, BigInt* n) {

    if (this == NULL || n == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    int subtract_status = 0;

    if (BigInt_has_same_sign(this, n)) {

        int cmp = 0;

        BigInt_abs_compare(this, n, &cmp);

        if (cmp > 0) {

            subtract_status = BigInt_abs_subtract(this, n);

        } else {

            BigInt* tmp = Bigint_deepcopy(n);

            subtract_status = BigInt_abs_subtract(tmp, this);

            _BigInt_relocate_drop(&tmp, this);

            BigInt_reverse_sign(this);
        }
        
    } else {
        subtract_status = BigInt_abs_add(this, n);
    }

    BigInt_strip(this);

    return subtract_status;
}


int BigInt_multiply(BigInt* this, BigInt* n) {

    if (this == NULL || n == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    BigInt* result = _BigInt_alloc(
        this->cap + n->cap, this->sign_flag
    );

    if (result == NULL) {
        return -1;
    }

    int multiply_status = BigInt_abs_multiply(
        this, n, result
    );

    if (multiply_status == -1) {
        return -1;
    }

    result->len = this->len + n->len;

    BigInt_strip(result);

    _BigInt_relocate_drop(&result, this);

    if (! BigInt_has_same_sign(this, n)) {
        BigInt_set_sign(this, BIG_INTEGER_IS_NEGATIVE);
    } else {
        BigInt_set_sign(this, BIG_INTEGER_IS_NOT_NEGATIVE);
    }

    return 0;
}


int BigInt_divide(BigInt* this, BigInt* n);


BigInt* _BigInt_alloc(int cap, BigIntSignFlag flag) {

    if (cap <= 0) {
        fprintf(stderr, BIG_INTEGER_CAPACITY_ERROR);
        return NULL;
    }

    BigInt* n = (BigInt*) malloc (sizeof(BigInt));

    if (n == NULL) {
        fprintf(stderr, BIG_INTEGER_CREATE_ERROR);
        return NULL;
    }

    n->number = (u_char*) malloc (sizeof(u_char) * cap);

    if (n->number == NULL) {
        fprintf(stderr, BIG_INTEGER_CREATE_ERROR);
        free(n);
        return NULL;
    }

    for (int i = 0; i < cap; i++) {
        n->number[i] = 0;
    }

    n->len = 0;

    n->cap = cap;

    n->sign_flag = flag;

    return n;
}


int _BigInt_realloc(BigInt* n, int new_cap) {

    if (n == NULL || new_cap < 1) {
        fprintf(stderr, BIG_INTEGER_REALLOC_SRC_ERROR);
        return -1;
    }

    u_char* new = (u_char*) realloc (
        n->number, 
        sizeof(u_char) * new_cap
    );

    if (new == NULL) {
        fprintf(stderr, BIG_INTEGER_REALLOC_ERROR);
        return -1;
    } else {
        n->number = new;
        n->cap = new_cap;
        return 0;
    }
}


int _BigInt_relocate_drop(BigInt** src, BigInt* dest) {

    if (src == NULL || *src == NULL || dest == NULL) {
        fprintf(stderr, BIG_INTEGER_ACCESS_EXCEPTION);
        return -1;
    }

    free(dest->number);

    dest->number = (*src)->number;

    dest->len = (*src)->len;

    dest->sign_flag = (*src)->sign_flag;

    dest->cap = (*src)->cap;

    free(*src);

    *src = NULL;

    return 0;
}
