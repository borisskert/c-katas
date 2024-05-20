#include <stdbool.h>
#include <string.h>

#define MAX_CHARS_COUNT 26

void increaseFor(signed int *counters, const char *str1);

void decreaseFor(signed int *counters, const char *str2);

bool noneNegative(const signed int *counters);

/**
 * https://www.codewars.com/kata/55c04b4cc56a697bb0000048/train/c
 * Changes:
 *   - use a simplified way to initialize the counters array
 * @param str1 first string (Only lower case letters will be used (a-z). No punctuation or array will be included.)
 * @param str2 string to be matched in str1 (Only lower case letters will be used (a-z). No punctuation or array will be included.)
 * @return `true` if a portion of str1 characters can be rearranged to match str2, otherwise returns `false`
 */
bool scramble(const char *str1, const char *str2) {
    signed int counters[MAX_CHARS_COUNT] = {0};

    increaseFor(counters, str1);
    decreaseFor(counters, str2);

    return noneNegative(counters);
}

void increaseFor(signed int *counters, const char *str1) {
    size_t size = strlen(str1);

    for (unsigned int index = 0; index < size; index++) {
        char c = str1[index];
        counters[c - 'a'] += 1;
    }
}

void decreaseFor(signed int *counters, const char *str2) {
    size_t size = strlen(str2);

    for (unsigned int index = 0; index < size; index++) {
        char c = str2[index];
        counters[c - 'a'] -= 1;
    }
}

bool noneNegative(const signed int *counters) {
    for (unsigned int index = 0; index < MAX_CHARS_COUNT; index++) {
        if (counters[index] < 0) {
            return false;
        }
    }

    return true;
}
