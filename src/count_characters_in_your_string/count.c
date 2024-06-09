#include <string.h>

#define COUNTS_SIZE 128

/**
 * https://www.codewars.com/kata/52efefcbcdf57161d4000091/train/c
 */
void count(const char *string, unsigned counts[COUNTS_SIZE]) {
    for (size_t index = 0; index < COUNTS_SIZE; index++) {
        counts[index] = 0;
    }

    size_t size = strlen(string);

    for (size_t i = 0; i < size; i++) {
        char c = string[i];
        counts[(int) c]++;
    }
}
