#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct isbn {
    char **groups;
    size_t count;
};

static struct isbn parse(const char *string);

static struct isbn convert_10_to_13(struct isbn);

static void format_into(struct isbn isbn, char *string);

static void free_isbn(struct isbn);

/**
 * https://www.codewars.com/kata/61ce25e92ca4fb000f689fb0/train/c
 * Changelog:
 *   - fixed some memory-leaks
 * @param ISBN_13 the output target string
 * @param ISBN_10 the input string
 * @return the output target string again
 */
char *ISBN_converter(char *ISBN_13, const char *ISBN_10) {
    struct isbn isbn = parse(ISBN_10);

    struct isbn isbn13 = convert_10_to_13(isbn);
    free_isbn(isbn);

    format_into(isbn13, ISBN_13);
    free_isbn(isbn13);

    return ISBN_13;
}

#define MAX_ISBN_DIGITS 17

static int *pure_digits(const struct isbn isbn, int *digitsCount) {
    *digitsCount = 0;

    int *digits = malloc(sizeof(int *) * MAX_ISBN_DIGITS);

    for (size_t groupIndex = 0; groupIndex < isbn.count; groupIndex++) {
        char *group = isbn.groups[groupIndex];
        size_t groupLength = strlen(group);

        for (size_t index = 0; index < groupLength; index++) {
            char groupDigit = group[index];

            if (groupDigit >= '0' && groupDigit <= '9') {
                digits[*digitsCount] = (int) (groupDigit - '0');
                *digitsCount = (*digitsCount) + 1;
            }
        }
    }

    return digits;
}

static char *checkdigit(const struct isbn isbn) {
    struct isbn tailed_isbn = isbn;
    tailed_isbn.count = isbn.count - 1;

    int digit_count;
    int *digits = pure_digits(tailed_isbn, &digit_count);

    int sum = 0;

    for (size_t index = 0; index < digit_count; index++) {
        int digit = digits[index];

        int factor = 1;
        if (index % 2 == 1) {
            factor = 3;
        }

        sum += digit * factor;
    }

    free(digits);

    sum = sum % 10;
    if (sum == 0) {
        return "0";
    }

    char digit = (char) (10 - sum + '0');

    char *checkdigit = malloc(sizeof(char *) * 2);
    checkdigit[0] = digit;
    checkdigit[1] = '\0';

    return checkdigit;
}

struct isbn convert_10_to_13(const struct isbn isbn) {
    char *prefix = malloc(sizeof(char) * 4);
    strcpy(prefix, "978");

    struct isbn isbn13;
    isbn13.count = isbn.count + 1;
    isbn13.groups = malloc(sizeof(char *) * isbn13.count);

    isbn13.groups[0] = prefix;

    size_t index = 1;
    for (; index < isbn13.count; index++) {
        char *src = isbn.groups[index - 1];
        char *dest = malloc(sizeof(char) * strlen(src));

        strcpy(dest, src);

        isbn13.groups[index] = dest;
    }

    isbn13.groups[isbn.count] = checkdigit(isbn13);;

    return isbn13;
}

/**
 * Split a string into n substrings by the specified delimiter
 * @param string the string to be split
 * @param n the substring count
 * @param delimiter the delimiter the string will be split up
 * @return an array of n strings
 */
static char **split(const char *string, size_t *n, const char *delimiter) {
    size_t maxLength = strlen(string);
    size_t maxByteLength = sizeof(char *) * maxLength;

    char **tokens = malloc(maxByteLength);

    /* Handle a copy into `strtok`, because the contents of this string are modified and broken into smaller strings (tokens). */
    char *copy = strdup(string);
    char *token = strtok(copy, delimiter);

    int actualLength = 0;
    while (token != NULL) {
        tokens[actualLength] = strdup(token);
        token = strtok(NULL, delimiter);
        actualLength = actualLength + 1;
    }

    free(copy);

    *n = actualLength;
    return tokens;
}

struct isbn parse(const char *string) {
    struct isbn isbn;
    isbn.groups = split(string, &(isbn.count), "-");

    return isbn;
}

/**
 * Join strings to a single string by using the specified delimiter
 * @param strings the strings to be joined
 * @param count the strings count
 * @param delimiter the used delimiter
 * @param target the target array the strings will be joined into
 */
static void join(const char **strings, const size_t count, const char *delimiter, char *target) {
    size_t delimiterLength = strlen(delimiter);

    size_t actualSize = 0;
    for (size_t index = 0; index < count; index++) {
        const char *word = strings[index];
        size_t wordLength = strlen(word);

        bool isLast = index >= count - 1;

        strcpy(target + actualSize, word);
        actualSize = actualSize + wordLength;

        if (isLast) {
            target[actualSize] = '\0';
        } else {
            strcpy(target + actualSize, delimiter);
            actualSize = actualSize + delimiterLength;
        }
    }
}

void format_into(struct isbn isbn, char *string) {
    join((const char **) isbn.groups, isbn.count, "-", string);
}

static void free_isbn(struct isbn isbn) {
    for (size_t index = 0; index < isbn.count; index++) {
        free(isbn.groups[index]);
    }

    free(isbn.groups);
}

// Again what learned:
// Use function `sprintf` to format values into a string
