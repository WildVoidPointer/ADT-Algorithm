#include <stdio.h>


int normal_power(int base, int n) {
    int res = base;

    for (int i = 1; i < n; i++) {
        res = res * base;
    }

    return res;
}


int fast_power_iteration(int base, int n) {
    int res = 1;

    while (n != 0) {

        if (n & 1) {
            res = res * base;
        }

        base = base * base;

        n = n >> 1;
    }

    return res;
}


int fast_power_recursion(int base, int n) {
    if (n == 0) {
        return 1;
    } else {

        int res = fast_power_recursion(base, n >> 1);

        if (n & 1) {
            return res * res * base;
        } else {
            return res * res;
        }
    }
}


long long fast_power_mod_iteration(long long base, int n, int mod) {
    long long res = 1;

    base = base % mod;

    while (n != 0) {

        if (n & 1) {
            res = (res * base) % mod;
        }

        base = (base * base) % mod;

        n = n >> 1;
    }

    return res;
}


int main() {
    printf("%d\n", normal_power(2, 4));
    printf("%d\n", fast_power_iteration(2, 5));
    printf("%d\n", fast_power_recursion(2, 6));
    printf(
        "%lld\n", 
        fast_power_mod_iteration(2, 100, 1000000007)
    ); // 976371285
}
