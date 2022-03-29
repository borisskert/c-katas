#include <stddef.h>

/**
 * https://www.codewars.com/kata/54521e9ec8e60bc4de000d6c/train/c
 * @param array sequence of integer values
 * @param n the amount of integers in the sequence
 * @return the subsequence sum
 */
int maxSequence(const int *array, size_t n) {
    int max = 0;
    int sum = 0;

    for (unsigned int index = 0; index < n; index++) {
        sum += array[index];

        if (sum < 0) {
            sum = 0;
        }

        if (max < sum) {
            max = sum;
        }
    }

    return max;
}
