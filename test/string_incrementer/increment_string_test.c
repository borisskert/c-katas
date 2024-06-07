#include <criterion/criterion.h>

extern char *incrementString(const char *str);

static void do_test(const char *str, const char *expected) {
    char *actual = incrementString(str);
    cr_assert_str_eq(actual, expected, "Expected: %s but got: %s", expected, actual);
    free(actual);
}

Test(StringIncrementerTest, StaticTests) {
    do_test("foobar000", "foobar001");
    do_test("foobar999", "foobar1000");
    do_test("foobar001", "foobar002");
    do_test("foobar99", "foobar100");
    do_test("foobar099", "foobar100");
    do_test("foobar00999", "foobar01000");
    do_test("foo", "foo1");
    do_test("foobar001", "foobar002");
    do_test("foobar1", "foobar2");
    do_test("1", "2");
    do_test("009", "010");
    do_test("", "1");
    do_test("fo99obar99", "fo99obar100");
    do_test("chcvwbzoxikugmjlqo", "chcvwbzoxikugmjlqo1");
    do_test("wzbuzowcpvkalwwybqrj338", "wzbuzowcpvkalwwybqrj339");
}
