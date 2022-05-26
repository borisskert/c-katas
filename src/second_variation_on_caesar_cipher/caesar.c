/*
 * https://www.codewars.com/kata/55084d3898b323f0aa000546/train/c
 */

#include <string.h>
#include <tgmath.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

#define PREFIX_LENGTH 2
#define ALPHABET_SIZE 26
#define AMOUNT_OF_CHUNKS 5

static char *prepareCiphertext(const char *string);

static void caesars(char *cleartext, int shift);

static char **chunksOf(const char *string, int *lg);

/**
 * @param lg the number of fragments that this function will return
 */
char **encode(char *string, int shift, int *lg) {
    char *ciphertext = prepareCiphertext(string);

    caesars(ciphertext + 1, shift);

    char **chunks = chunksOf(ciphertext, lg);
    free(ciphertext);

    return chunks;
}

static char *join(const char **strings, size_t count, const char *delimiter);

static int extractShift(const char *joined);

/**
 * @param size the given number of fragments to decode
 */
char *decode(char **strings, int size) {
    char *joined = join((const char **) strings, size, "");
    int shift = extractShift(joined);

    caesars(joined + PREFIX_LENGTH, shift);

    size_t oldLength = strlen(joined);
    memmove(joined, joined + PREFIX_LENGTH, oldLength - PREFIX_LENGTH);
    joined[oldLength - PREFIX_LENGTH] = '\0';

    return joined;
}

int extractShift(const char *joined) {
    char prefix[PREFIX_LENGTH];
    strncpy(prefix, joined, PREFIX_LENGTH);

    return -1 * (prefix[1] - prefix[0]) % ALPHABET_SIZE;
}

char *prepareCiphertext(const char *string) {
    char *ciphertext = malloc(sizeof(char) * (strlen(string) + PREFIX_LENGTH));

    ciphertext[0] = (char) tolower(string[0]);
    ciphertext[1] = (char) tolower(string[0]);
    strcpy(ciphertext + PREFIX_LENGTH, string);

    return ciphertext;
}

/**
 * encrypt/decrypt specified string in place
 */
void caesars(char *cleartext, const int shift) {
    size_t length = strlen(cleartext);

    for (unsigned int index = 0; index < length; index++) {
        char c = cleartext[index];

        int offset;
        if (c >= 'A' && c <= 'Z') {
            offset = 'A';
        } else if (c >= 'a' && c <= 'z') {
            offset = 'a';
        } else {
            continue;
        }

        cleartext[index] = (char) (((c - offset + shift + ALPHABET_SIZE) % ALPHABET_SIZE) + offset);
    }
}

char **chunksOf(const char *string, int *lg) {
    size_t inputLength = strlen(string);

    unsigned int chunkSize = ceil((double) inputLength / (double) AMOUNT_OF_CHUNKS);
    char **chunksArray = malloc(sizeof(char *) * AMOUNT_OF_CHUNKS);

    for (unsigned int index = 0; index < AMOUNT_OF_CHUNKS; index++) {
        chunksArray[index] = malloc(sizeof(char) * (chunkSize + 1));
        strncpy(chunksArray[index], string + index * chunkSize, chunkSize);
        chunksArray[index][chunkSize] = '\0';
    }

    *lg = (int) ceil((double) inputLength / (double) chunkSize);

    return chunksArray;
}

/**
 * Extend the allocated memory for the specified string
 * @param source the source string
 * @param extensionSize the size your string will be extended with
 * @return the same string but within an extended buffer size
 */
static char *extendStringBuffer(const char *source, size_t extensionSize) {
    size_t oldSize = strlen(source);

    void *destination = malloc(oldSize + extensionSize);
    strcpy(destination, source);

    return destination;
}

/**
 * Join strings to a single string by using the specified delimiter
 * @param strings the strings to be joined
 * @param count the strings count
 * @param delimiter the used delimiter
 * @return a strings joined to a single string
 */
static char *join(const char **strings, const size_t count, const char *delimiter) {
    const size_t supposedWordLength = 5;
    size_t delimiterLength = strlen(delimiter);

    size_t supposedSize = sizeof(char) * count * supposedWordLength + (count - 1) * delimiterLength;
    char *joinedWords = malloc(supposedSize);

    size_t actualSize = 0;
    for (size_t index = 0; index < count; index++) {
        const char *word = strings[index];
        size_t wordLength = strlen(word);

        bool isLast = index >= count - 1;
        size_t neededSize;

        if (isLast) {
            neededSize = actualSize + wordLength + 1;
        } else {
            neededSize = actualSize + wordLength + delimiterLength;
        }

        if (neededSize < supposedSize) {
            char *extended = extendStringBuffer(joinedWords, supposedSize);
            supposedSize = supposedSize * 2;

            free(joinedWords);
            joinedWords = extended;
        }

        strcpy(joinedWords + actualSize, word);
        actualSize = actualSize + wordLength;

        if (isLast) {
            joinedWords[actualSize] = '\0';
        } else {
            strcpy(joinedWords + actualSize, delimiter);
            actualSize = actualSize + delimiterLength;
        }
    }

    return joinedWords;
}
