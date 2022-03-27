#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct weight {
    char *value;
    unsigned int sum;
};

struct weights {
    struct weight *values;
    size_t size;
};

static struct weights parse(const char *string);

static char *toString(struct weights weights);

static int compareWeights(const void *a, const void *b);

static void freeWeights(struct weights weights);

/**
 * https://www.codewars.com/kata/55c6126177c9441a570000cc/train/c
 * @param s the weights as a string (space-separated)
 * @return the sorted weights as a string (space-separated)
 */
char *orderWeight(const char *s) {
    struct weights weights = parse(s);

    qsort(weights.values, weights.size, sizeof(struct weight), compareWeights);

    char *weightsString = toString(weights);

    freeWeights(weights);

    return weightsString;
}

static int compareWeights(const void *a, const void *b) {
    struct weight *weightA = (struct weight *) a;
    struct weight *weightB = (struct weight *) b;

    if (weightA->sum == weightB->sum) {
        return strcmp(weightA->value, weightB->value);
    }

    return ((int) weightB->sum) - ((int) weightA->sum);
}

static const char **toStrings(struct weights weights) {
    size_t count = weights.size;
    const char **strings = malloc(sizeof(char *) * count);

    for (unsigned int index = 0; index < count; index++) {
        strings[index] = weights.values[index].value;
    }

    return strings;
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
    memcpy(destination, source, oldSize);

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

/**
 * Join words to a sentence by using a space as delimiter
 * @param words the words as string-array
 * @param count the count of words
 * @return the sentence as string
 */
static char *unwords(const char **words, const size_t count) {
    return join(words, count, " ");
}

static char *toString(const struct weights weights) {
    const char **strings = toStrings(weights);

    char *string = unwords(strings, weights.size);
    free(strings);

    return string;
}

static unsigned int toWeightSum(const char *string) {
    unsigned int index = 0;
    char c = string[index];

    unsigned int sum = 0;

    do {
        unsigned int value = '0' - c;

        sum += value;

        index++;
        c = string[index];
    } while (c != '\0');

    return sum;
}

static struct weight toWeight(char *string) {
    struct weight weight;

    weight.value = string;
    weight.sum = toWeightSum(string);

    return weight;
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

static struct weights parse(const char *string) {
    size_t wordsCount = -1;

    /* Handle a copy into `strtok`, because the contents of this string are modified and broken into smaller strings (tokens). */
    char *copy = strdup(string);
    char **wordsArray = words(copy, &wordsCount);

    struct weights weights;

    weights.values = malloc(sizeof(struct weight) * wordsCount);
    weights.size = wordsCount;

    for (unsigned int index = 0; index < wordsCount; index++) {
        weights.values[index] = toWeight(wordsArray[index]);
    }

    free(wordsArray);
    free(copy);

    return weights;
}

void freeWeights(struct weights weights) {
    for (unsigned int index = 0; index < weights.size; index++) {
        struct weight weight = weights.values[index];
        free(weight.value);
    }
}
