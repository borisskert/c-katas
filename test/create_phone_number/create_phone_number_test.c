#include <criterion/criterion.h>

char *create_phone_number(char phone_number[15], const unsigned char nums[10]);

void assert_eq(char *actual, const char *expected) {
    if (!actual)
        cr_assert_fail("*Actual*: NULL\nExpected: \"%s\"", expected);
    else
        cr_assert_str_eq(actual, expected, "*Actual*: \"%s\"\nExpected: \"%s\"", actual, expected);
}

Test(Sample_Test, should_return_the_phone_number) {
    char phnum[15];
    assert_eq(create_phone_number(phnum, (const unsigned char[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}), "(123) 456-7890");
    assert_eq(create_phone_number(phnum, (const unsigned char[]) {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}), "(111) 111-1111");
    assert_eq(create_phone_number(phnum, (const unsigned char[]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 0}), "(123) 456-7890");
}
