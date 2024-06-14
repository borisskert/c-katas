#include <stdlib.h>
#include <string.h>

/*
 * The Vowel Code
 * https://www.codewars.com/kata/53697be005f803751e0015aa/train/c
 */

static char encode_char(char c);

char *encode(const char *string) {
    size_t length = strlen(string);

    char *result = (char *) malloc((length + 1) * sizeof(char));
    result[length] = '\0';

    for (size_t i = 0; i < length; i++) {
        result[i] = encode_char(string[i]);
    }

    return result;
}

static char decode_char(char c);

char *decode(const char *string) {
    size_t length = strlen(string);

    char *result = (char *) malloc((length + 1) * sizeof(char));
    result[length] = '\0';

    for (size_t i = 0; i < length; i++) {
        result[i] = decode_char(string[i]);
    }

    return result;
}

static char encode_char(char c) {
    if (c == 'a') {
        return '1';
    } else if (c == 'e') {
        return '2';
    } else if (c == 'i') {
        return '3';
    } else if (c == 'o') {
        return '4';
    } else if (c == 'u') {
        return '5';
    } else {
        return c;
    }
}

static char decode_char(char c) {
    if (c == '1') {
        return 'a';
    } else if (c == '2') {
        return 'e';
    } else if (c == '3') {
        return 'i';
    } else if (c == '4') {
        return 'o';
    } else if (c == '5') {
        return 'u';
    } else {
        return c;
    }
}
