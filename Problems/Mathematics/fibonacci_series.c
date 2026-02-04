#include <stdio.h>


int fib_series_iteration(int* buf, int n) {
    if (n >= 1) buf[0] = 0;
    if (n >= 2) buf[1] = 1;
    for (int i = 2; i < n; i++) {
        buf[i] = buf[i - 1] + buf[i - 2];
    }
    return 0;
}


int fib_series_recursion(int* buf, int n) {

    if (buf[n - 1] != -1) {
        return buf[n - 1];
    }

    if (n == 1) {
        return buf[n - 1] = 0;
    }

    if (n == 2) {
        return buf[n - 1] = 1;
    }
    
    buf[n - 1] = fib_series_recursion(buf, n - 1) +
                fib_series_recursion(buf, n - 2);

    return buf[n - 1];
}


int main(int argc, char const *argv[])
{
    int length = 10;
    int fibonacci[10];

    for (int i = 0; i < length; i++) {
        fibonacci[i] = -1;
    }

    fib_series_recursion(fibonacci, length);
    fib_series_iteration(fibonacci, length);

    for (int i = 0; i < length; i++) {
        printf("%d ", fibonacci[i]);
    }
    
    putc('\n', stdout);
    return 0;
}
