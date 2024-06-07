#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * https://www.codewars.com/kata/54a91a4883a7de5d7800009c/train/c
 */
char *incrementString(const char *str);

static void increment(char *str) {
    size_t length = strlen(str);

    if (length == 0) {
        str[0] = '1';
        return;
    }

    int index = (int) (length - 1);
    bool need_to_shift = false;

    while (index >= 0) {
        char last = str[index];

        if (last <= '8' && last >= '0') {
            str[index] = (char) ((int) last + 1);
            break;
        } else if (last == '9') {
            str[index] = '0';
            index--;
        } else {
            str[++index] = '1';
            need_to_shift = true;
            break;
        }
    }

    if (need_to_shift) {
        index++;

        while (index <= length) {
            str[index] = '0';
            index++;
        }
    }
}

char *incrementString(const char *str) {
    size_t length = strlen(str);

    char *result = malloc((length + 2) * sizeof(char));
    memcpy(result, str, length);
    result[length] = '\0';
    result[length + 1] = '\0';

    increment(result);

    return result;
}

// #againwhatlearned
// Use `asprintf(&buf, "%.*s%0*d", i + 1, str, len - i - 1, n + 1);` function from `<stdio.h>` to allocate a
// right-sized string and format values into.
