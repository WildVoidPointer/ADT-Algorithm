#include "big_integer.h"

#include <stdio.h>


static int BigInt_add_Test() {
    u_char* num1 = "10000012345";
    int num1_length = 11;

    u_char* num2 = "90000092345";
    int num2_length = 11;

    BigInt* big_num1 = BigInt_of_chars(num1, num1_length);

    BigInt* big_num2 = BigInt_of_chars(num2, num2_length);

    if (big_num1 == NULL || big_num2 == NULL) {
        printf("Create Failed\n");
        return 1;
    }

    BigInt_display(big_num1);
    BigInt_display(big_num2);

    BigInt_add(big_num1, big_num2);

    BigInt_display(big_num1);
    BigInt_display(big_num2);

    BigInt_destroy(&big_num1);
    BigInt_destroy(&big_num2);
}


static int BigInt_subtract_Test() {
    u_char* num1 = "0023";
    u_char* num2 = "0032";
    int num_len = 4;

    BigInt* big_num1 = BigInt_of_chars(num1, num_len);
    BigInt* big_num2 = BigInt_of_chars(num2, num_len);

    BigInt_subtract(big_num1, big_num2);

    BigInt_display(big_num1);
    BigInt_display(big_num2);

    BigInt_destroy(&big_num1);
    BigInt_destroy(&big_num2);
}


static int BigInt_multiply_Test() {
    u_char* num1 = "-0023";
    u_char* num2 = "-0032";
    int num_len = 5;

    BigInt* big_num1 = BigInt_of_chars(num1, num_len);
    BigInt* big_num2 = BigInt_of_chars(num2, num_len);

    BigInt_display(big_num1);
    BigInt_display(big_num2);

    BigInt_multiply(big_num1, big_num2);

    BigInt_display(big_num1);
    BigInt_display(big_num2);

    BigInt_destroy(&big_num1);
    BigInt_destroy(&big_num2);
}


int main () {
    BigInt_multiply_Test();
    
}