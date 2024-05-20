#include <stdlib.h>
#include <criterion/criterion.h>

extern long long *smallest(long long n);

static void dotest(long long n, const long long expected[3]);

Test(smallest, sampleTests) {
    dotest(261235, (long long[3]) {126235, 2, 0});
    dotest(209917, (long long[3]) {29917, 0, 1});
    dotest(285365, (long long[3]) {238565, 3, 1});
    dotest(269045, (long long[3]) {26945, 3, 0});
    dotest(296837, (long long[3]) {239687, 4, 1});
}

static void dotest(long long n, const long long expected[3]) {
    long long *actual = smallest(n);
    cr_assert_arr_eq(actual, expected, 3 * sizeof *expected,
                     "for n = %lld\nexpected { %lld, %lld, %lld }\nbut got { %lld, %lld, %lld }",
                     n,
                     expected[0], expected[1], expected[2],
                     actual[0], actual[1], actual[2]
    );
    free(actual);
}
