#include <criterion/criterion.h>
#include <stdbool.h>

bool validParentheses(const char *strin);

Test(Sample_Tests, should_pass_all_the_tests_provided) {
    cr_assert_eq(validParentheses("  ("), false);
    cr_assert_eq(validParentheses(")test"), false);
    cr_assert_eq(validParentheses(""), true);
    cr_assert_eq(validParentheses("hi())("), false);
    cr_assert_eq(validParentheses("hi(hi)()"), true);
}
