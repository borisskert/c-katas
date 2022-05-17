#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static char **words(const char *sentence, size_t *wordsCount);

static void reverseWord(char *word);

static void unwords(const char **words, const size_t count, char *target);

static void map(char **strings, const size_t size, void (*mapperFunction)(char *));

/**
 * https://www.codewars.com/kata/5264d2b162488dc400000001/train/c
 * do not allocate memory for return string
 * assign the value to the pointer "result"
 * @param sentence the words to be spun
 * @param result the spun words
 */
void spin_words(const char *sentence, char *result) {
    size_t wordsCount = -1;
    char **words_array = words(sentence, &wordsCount);

    map(words_array, wordsCount, reverseWord);

    unwords(words_array, wordsCount, result);
}

static void map(char **strings, const size_t size, void (*mapperFunction)(char *)) {
    for (unsigned index = 0; index < size; index++) {
        char *word = strings[index];
        mapperFunction(word);
    }
}

static void reverse(char *word) {
    size_t length = strlen(word);

    for (unsigned int index = 0; index < (length / 2); index++) {
        char letter = word[index];

        word[index] = word[length - index - 1];
        word[length - index - 1] = letter;
    }
}

static void reverseWord(char *word) {
    size_t length = strlen(word);

    if (length >= 5) {
        reverse(word);
    }
}

/**
 * Join strings to a single string by using the specified delimiter
 * @param strings the strings to be joined
 * @param count the strings count
 * @param delimiter the used delimiter
 * @param target the target array the strings will be joined into
 */
void join(const char **strings, const size_t count, const char *delimiter, char *target) {
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

/**
 * Join words to a sentence by using a space as delimiter
 * @param words the words as string-array
 * @param count the count of words
 * @param target the target string the sentence will be written into
 */
void unwords(const char **words, const size_t count, char *target) {
    join(words, count, " ", target);
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

/**
 * Split a sentence (as string) by spaces into words
 * @param sentence the sentence to be split
 * @return the words and its count as struct
 */
static char **words(const char *sentence, size_t *wordsCount) {
    return split(sentence, wordsCount, " ");
}
