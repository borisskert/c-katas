#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
 * Changelog:
 *   - made helper functions `static`
 *   - use `memcpy` C library function
 */

static void reduce(char **arr, int index, int *reducedSize);

static char **copyArray(char **arr, int size);

/**
 * https://www.codewars.com/kata/550f22f4d758534c1100025a/train/c
 * @param array directions to reduce
 * @param size size of arr
 * @param reducedSize size of returned array
 * @return reduced directions as array of strings
 */
char **dirReduc(char **array, int size, int *reducedSize) {
    if (size == 0) {
        *reducedSize = 0;
        return malloc(0);
    }

    *reducedSize = size;
    char **copy = copyArray(array, size);
    reduce(copy, 0, reducedSize);

    return copy;
}

char **copyArray(char **arr, int size) {
    int bytesCount = sizeof(char *) * size;

    char **copy = malloc(bytesCount);
    memcpy(copy, arr, bytesCount);

    return copy;
}

static bool areOpposites(char *a, char *b);

static void shiftLeft(char **array, int size, int offset);

static void reduce(char **arr, int index, int *reducedSize) {
    do {
        char *first = arr[index];
        char *second = arr[index + 1];

        if (areOpposites(first, second)) {
            shiftLeft(arr + index, *reducedSize - index, 2);

            if (index > 0) {
                index = index - 1;
            }

            *reducedSize = (*reducedSize - 2);
        } else {
            index = index + 1;
        }
    } while (index < *reducedSize - 1);
}

static void shiftLeft(char **array, int size, int offset) {
    if (offset >= size) {
        return;
    }

    for (int index = 0; index < size - offset; index++) {
        array[index] = array[index + offset];
    }
}

static bool areOpposites(char *a, char *b) {
    return (strcmp(a, "NORTH") == 0 && strcmp(b, "SOUTH") == 0)
           || (strcmp(b, "NORTH") == 0 && strcmp(a, "SOUTH") == 0)
           || (strcmp(a, "EAST") == 0 && strcmp(b, "WEST") == 0)
           || (strcmp(b, "EAST") == 0 && strcmp(a, "WEST") == 0);
}
