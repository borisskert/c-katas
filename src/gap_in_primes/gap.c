#include <stdlib.h>
#include <stdbool.h>

/**
 * https://www.codewars.com/kata/561e9c843a2ef5a40c0000a4/train/c
 */
long long *gap(int g, long long m, long long n);

bool is_prime(long long n) {
    if (n <= 1) {
        return false;
    }

    if (n <= 3) {
        return true;
    }

    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

long long next_prime(long long n) {
    if (n % 2 == 0) {
        n++;
    }

    while (!is_prime(n)) {
        n += 2;
    }

    return n;
}

long long *gap(int g, long long m, long long n) {
    long long *result = (long long *) malloc(2 * sizeof(long long));
    result[0] = 0;
    result[1] = 0;

    long long a = next_prime(m);
    long long b = next_prime(a + 2);

    while (b - a != g && b <= n) {
        a = b;
        b = next_prime(b + 2);
    }

    if (b <= n) {
        result[0] = a;
        result[1] = b;
    }

    return result;
}
