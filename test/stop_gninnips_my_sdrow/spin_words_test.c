#include <criterion/criterion.h>

void spin_words(const char *sentence, char *result);

void tester(const char *sentence, char *result);

Test(Example_Tests, should_pass_all_the_tests_provided) {
    tester("Welcome", "emocleW");
    tester("spam", "spam");
    tester("This is a test", "This is a test");
    tester("This is another test", "This is rehtona test");
}

void tester(const char *sentence, char *expected) {
    char submitted[30 * 14 + 1];
    spin_words(sentence, (char *) &submitted);
    if (strcmp(submitted, expected)) {
        cr_assert_fail(
                "Sentence:  \"%s\"\n \nSubmitted: \"%s\"\n \nExpected:  \"%s\"\n \n",
                sentence, submitted, expected
        );
    }
    cr_assert(1);
}
