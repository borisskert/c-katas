#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * https://www.codewars.com/kata/530e15517bc88ac656000716/train/c
 */
char *rot13(const char *src);

bool isLowercase(char c) { return c >= 'a' && c <= 'z'; }

bool isUppercase(char c) { return c >= 'A' && c <= 'Z'; }

char encrypt(char c) {
    if (isLowercase(c)) {
        return (char) ((c - 'a' + 13) % 26 + 'a');
    } else if (isUppercase(c)) {
        return (char) ((c - 'A' + 13) % 26 + 'A');
    } else {
        return c;
    }
}

char *rot13(const char *src) {
    size_t length = strlen(src);

    char *result = (char *) malloc(length + 1);
    result[length] = '\0';

    for (size_t i = 0; src[i] != '\0'; i++) {
        result[i] = encrypt(src[i]);
    }

    return result;
}
