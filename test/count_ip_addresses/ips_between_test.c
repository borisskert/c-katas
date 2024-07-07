#include <inttypes.h>
#include <criterion/criterion.h>

extern uint32_t ips_between(const char *start, const char *end);

static void do_test(const char *start, const char *end, uint32_t expected);

Test(ips_between_tests_suite, sample_tests) {
    do_test("10.0.0.0", "10.0.0.50", 50);
    do_test("20.0.0.10", "20.0.1.0", 246);
    do_test("0.0.0.0", "255.255.255.255", UINT32_MAX);
}

static void do_test(const char *start, const char *end, uint32_t expected) {
    uint32_t actual = ips_between(start, end);
    cr_assert_eq(actual, expected,
                 "for (start = %s ; end = %s)\nexpected %"PRIu32" but got %"PRIu32,
                 start, end, expected, actual
    );
}
