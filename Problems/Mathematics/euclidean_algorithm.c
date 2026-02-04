#include <stdio.h>


int gcd_with_recursion(int dividend, int divisor) {
    if (divisor > 0) {
        return gcd_with_recursion(
            divisor, dividend % divisor
        );
    } else {
        return dividend;
    }
}


int gcd_with_iteration(int devidend, int divisor) {
    int remainder = devidend % divisor;

    while (remainder != 0) {
        devidend = divisor;
        divisor = remainder;
        remainder = devidend % divisor;
    }

    return divisor;
}


int main() {
    printf("%d\n", gcd_with_recursion(7, 35));
    printf("%d\n", gcd_with_iteration(33, 11));
}
