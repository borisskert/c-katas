#include <stdlib.h>

/*
 * https://www.codewars.com/kata/573992c724fc289553000e95/train/c
 */

struct pair {
    unsigned short i;
    unsigned short j;
};

struct result {
    long long n;
    struct pair pair;
};

static struct result find_smallest(long long n);

long long *smallest(long long n) {
    long long *result = malloc(3 * sizeof(long long));

    struct result smallest_result = find_smallest(n);

    result[0] = smallest_result.n;
    result[1] = smallest_result.pair.i;
    result[2] = smallest_result.pair.j;

    return result;
}

struct digits {
    unsigned short count;
    unsigned short array[19]; // max value of `long long` is 9223372036854775807
};

static struct digits to_digits(long long n) {
    struct digits result = {0, {0}};

    while (n > 0) {
        result.array[result.count++] = n % 10;
        n /= 10;
    }

    return result;
}

static long long from_digits(struct digits digits) {
    long long result = 0;

    for (unsigned short index = 0; index < digits.count; index++) {
        result = result * 10 + digits.array[digits.count - index - 1];
    }

    return result;
}

static long long move_digit(long long n, unsigned short i, unsigned short j) {
    struct digits digits = to_digits(n);

    if (i == j) {
        return n;
    }

    unsigned short from = digits.count - i - 1;
    unsigned short to = digits.count - j - 1;

    if (from < to) {
        for (unsigned short index = from; index < to; index++) {
            unsigned short temp = digits.array[index];
            digits.array[index] = digits.array[index + 1];
            digits.array[index + 1] = temp;
        }
    } else {
        for (unsigned short index = from; index > to; index--) {
            unsigned short temp = digits.array[index];
            digits.array[index] = digits.array[index - 1];
            digits.array[index - 1] = temp;
        }
    }

    return from_digits(digits);
}

static struct result find_smallest(long long n) {
    struct digits digits = to_digits(n);
    struct result result = {n, {0, 0}};

    for (unsigned short i = 0; i < digits.count; i++) {
        for (unsigned short j = 0; j < digits.count; j++) {
            long long moved = move_digit(n, i, j);

            if (moved < result.n) {
                result.n = moved;

                if (i == j) {
                    result.pair.i = 0;
                    result.pair.j = 0;
                } else {
                    result.pair.i = i;
                    result.pair.j = j;
                }
            }
        }
    }

    return result;
}
