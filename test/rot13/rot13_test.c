#include <criterion/criterion.h>
#include <stddef.h>

// replace with the actual method being tested
char *rot13(const char *src);

Test(BasicTests, ShouldPassAllTheTestsProvided) {
    // Test 01
    {
        const char *src = "test";
        const char *expected = "grfg";
        char *actual = rot13(src);

        if (actual) {
            cr_assert_str_eq(expected, actual, "Expected: \"%s\", Actual: \"%s\"\n", expected, actual);
        } else {
            cr_assert(0, "Expected: \"%s\", Actual: NULL", expected);
        }

        /* It's okay if actual == NULL and we free a NULL pointer. */
        free(actual);
        actual = NULL;
    }

    // Test 02
    {
        const char *src = "Test";
        const char *expected = "Grfg";
        char *actual = rot13(src);

        if (actual) {
            cr_assert_str_eq(expected, actual, "Expected: \"%s\", Actual: \"%s\"\n", expected, actual);
        } else {
            cr_assert(0, "Expected: \"%s\", Actual: NULL", expected);
        }

        /* It's okay if actual == NULL and we free a NULL pointer. */
        free(actual);
        actual = NULL;
    }
}
