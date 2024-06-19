#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Pair Pair;

/**
 * https://www.codewars.com/kata/55aa075506463dac6600010d/train/c
 */
Pair **listSquared(long long m, long long n, int *length);

struct Pair {
    long long first;
    long long snd;
};

static long long *divisors(long long n, int *length);

static long long squareSum(const long long *n, int length);

static bool isSquare(long long n);

static Pair **append(Pair **pairs, int *length, long long int i);

static Pair *newPair(long long first, long long snd) {
    Pair *pair = malloc(sizeof(Pair));
    pair->first = first;
    pair->snd = snd;

    return pair;
}

Pair **listSquared(long long m, long long n, int *length) {
    Pair **pairs = malloc(0);

    for (long long i = m; i <= n; i++) {
        pairs = append(pairs, length, i);

        if (pairs == NULL) {
            free(pairs);
            return NULL;
        }
    }

    return pairs;
}

static Pair **append(Pair **pairs, int *length, long long int i) {
    int divsLength;
    long long *divs = divisors(i, &divsLength);

    if (divs == NULL) {
        return NULL;
    }

    long long sum = squareSum(divs, divsLength);

    if (isSquare(sum)) {
        Pair **newPairs = realloc(pairs, (*length + 1) * sizeof(Pair *));

        if (newPairs == NULL) {
            return NULL;
        }

        pairs = newPairs;
        pairs[*length] = newPair(i, sum);

        (*length)++;
    }

    free(divs);

    return pairs;
}

static long long *divisors(long long n, int *length) {
    long long *divs = malloc(0);
    *length = 0;

    for (long long i = 1; i <= n; i++) {
        if (n % i == 0) {
            long long *newDivs = realloc(divs, (*length + 1) * sizeof(long long));

            if (newDivs == NULL) {
                free(divs);
                return NULL;
            }

            divs = newDivs;
            divs[*length] = i;

            (*length)++;
        }
    }

    return divs;
}

static long long squareSum(const long long *n, int length) {
    long long sum = 0;

    for (int i = 0; i < length; i++) {
        sum += n[i] * n[i];
    }

    return sum;
}

static bool isSquare(long long n) {
    long long i = (long long) sqrt((double) n);
    return i * i == n;
}
