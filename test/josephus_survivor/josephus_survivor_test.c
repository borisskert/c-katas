#include <criterion/criterion.h>

int josephus_survivor(int n, int k);

static void tester(int n, int k, int exp) {
    int actual = josephus_survivor(n, k);
    cr_assert_eq(actual, exp, "Actual: %i, Expected: %i", actual, exp);
}

Test(josephus_survivor_test, examples) {
    tester(7, 3, 4);
    tester(11, 19, 10);
    tester(1, 300, 1);
    tester(14, 2, 13);
    tester(100, 1, 100);
}
