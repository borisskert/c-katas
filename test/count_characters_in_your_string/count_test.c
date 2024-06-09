#include <criterion/criterion.h>
#include <stdio.h>

#define COUNTS_SIZE 128

extern void count(const char *string, unsigned counts[COUNTS_SIZE]);

static void tester(const char *string, const unsigned expected[COUNTS_SIZE]);

Test(count, Sample_Tests) {
    {
        const unsigned expected[COUNTS_SIZE] = { ['a'] = 2, ['b'] = 1 };
        tester("aba", expected);
    }
    {
        const unsigned expected[COUNTS_SIZE] = { 0 };
        tester("", expected);
    }
    {
        const unsigned expected[COUNTS_SIZE] = { ['a'] = 2 };
        tester("aa", expected);
    }
    {
        const unsigned expected[COUNTS_SIZE] = { ['a'] = 2, ['b'] = 2 };
        tester("aabb", expected);
    }
}

void tester(const char *string, const unsigned expected[COUNTS_SIZE]) {
    unsigned submitted[COUNTS_SIZE];
    for(size_t index = 0; index < COUNTS_SIZE; index++) {
        submitted[index] = rand() % 10;
    }
    count(string, submitted);
    for(size_t index = 0; index < COUNTS_SIZE; index++) {
        if(submitted[index] != expected[index]) {
            char sub_str[22 * COUNTS_SIZE + 1];
            size_t index = 0;
            size_t position = sprintf(sub_str, "{");
            while(index < COUNTS_SIZE) {
                position += sprintf(sub_str + position, "%u, ", submitted[index]);
                index += 1;
            }
            sprintf(sub_str + position - 2, "}");
            char exp_str[22 * COUNTS_SIZE + 1];
            index = 0;
            position = sprintf(exp_str, "{");
            while(index < COUNTS_SIZE) {
                position += sprintf(exp_str + position, "%u, ", expected[index]);
                index += 1;
            }
            sprintf(exp_str + position - 2, "}");
            cr_assert_fail(
                    "< Incorrect Resuls >\n \nstring = \"%s\"\n \nSubmitted: %s\n \nExpected:  %s\n \n",
                    string,             sub_str,          exp_str
            );
        }
    }
    cr_assert(1);
}
