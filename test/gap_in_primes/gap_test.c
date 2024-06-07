#include <stdlib.h>
#include <string.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

extern long long *gap(int g, long long m, long long n);

static void dotest(int g, long long start, long long nd, long long expr[2]) {
    long long *act = gap(g, start, nd);

    cr_assert_arr_eq(expr, act, 2 * sizeof(long long), "Arrays are not equal: %lld, %lld", act[0], act[1]);

    free(act);
    act = NULL;
}

Test(gap, ShouldPassAllTheTestsProvided) {

    dotest(2, 100, 110, (long long[]) {101, 103});
    dotest(4, 100, 110, (long long[]) {103, 107});
    dotest(6, 100, 110, (long long[]) {0, 0});
    dotest(8, 300, 400, (long long[]) {359, 367});
}
