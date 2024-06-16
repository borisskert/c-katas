#include <stdlib.h>
#include <printf.h>

// https://www.codewars.com/kata/5514e5b77e6b2f38e0000ca9/train/c
int *up_array(const int *arr, unsigned *count) {
    if (*count == 0 || arr == NULL) {
        return NULL;
    }

    int *result = (int *) malloc((*count + 1) * sizeof(int));

    int index = (int) *count - 1;
    for (; index >= 0; index--) {
        if (arr[index] < 0 || arr[index] > 9) {
            free(result);
            *count = 0;

            return NULL;
        }

        if (index == 0 && arr[index] == 9) {
            result[0] = 1;
            result[*count] = 0;
            (*count)++;

            return result;
        }

        if (arr[index] == 9) {
            result[index] = 0;
        } else {
            result[index] = arr[index] + 1;
            break;
        }
    }

    for (index -= 1; index >= 0; index--) {
        if (arr[index] < 0 || arr[index] > 9) {
            free(result);
            *count = 0;

            return NULL;
        }

        result[index] = arr[index];
    }

    return result;
}
