#include <memory.h>
#include <stdlib.h>

/*
 * https://www.codewars.com/kata/5270d0d18625160ada0000e4/train/c
 */

#define SIZE 5

static int *copyIntsSorted(const int *src);

static int collect_score(int *dice, unsigned int size);

int score(const int dice[SIZE]) {
    int *copy = copyIntsSorted(dice);
    int collected_score = collect_score(copy, SIZE);

    free(copy);

    return collected_score;
}

static int compareInts(const void *a, const void *b) {
    int *intA = (int *) a;
    int *intB = (int *) b;

    return *intA - *intB;
}

static int *copyIntsSorted(const int *src) {
    int *copy = malloc(SIZE * sizeof(const int));
    memcpy(copy, src, SIZE * sizeof(const int));
    qsort(copy, SIZE, sizeof(const int), compareInts);

    return copy;
}

int collect_score(int *dice, unsigned int size) {
    if (size < 1) {
        return 0;
    }

    if (size >= 3 && dice[0] == dice[1] && dice[1] == dice[2]) {
        int score = 0;

        if (dice[0] == 1) {
            score += 1000;
        }
        if (dice[0] == 6) {
            score += 600;
        }
        if (dice[0] == 5) {
            score += 500;
        }
        if (dice[0] == 4) {
            score += 400;
        }
        if (dice[0] == 3) {
            score += 300;
        }
        if (dice[0] == 2) {
            score += 200;
        }

        return score + collect_score(dice + 3, size - 3);
    }

    if (dice[0] == 1) {
        return 100 + collect_score(dice + 1, size - 1);
    }
    if (dice[0] == 5) {
        return 50 + collect_score(dice + 1, size - 1);
    }

    return collect_score(dice + 1, size - 1);
}
