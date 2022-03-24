#include <criterion/criterion.h>
#include <stdbool.h>

bool scramble(const char *, const char *);

Test(BasicTests, should_pass_all_the_tests_provided) {
    cr_assert_eq(scramble("rkqodlw", "world"), true);
    cr_assert_eq(scramble("cedewaraaossoqqyt", "codewars"), true);
    cr_assert_eq(scramble("katas", "steak"), false);
    cr_assert_eq(scramble("scriptjavx", "javascript"), false);
    cr_assert_eq(scramble("scriptingjava", "javascript"), true);
    cr_assert_eq(scramble("scriptsjava", "javascript"), true);
    cr_assert_eq(scramble("javscripts", "javascript"), false);
    cr_assert_eq(scramble("aabbcamaomsccdd", "commas"), true);
    cr_assert_eq(scramble("commas", "commas"), true);
    cr_assert_eq(scramble("sammoc", "commas"), true);
}
