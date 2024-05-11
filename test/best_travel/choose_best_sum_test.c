#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <criterion/criterion.h>

int chooseBestSum(int t, int k, int ls[], int szls);

static void dotest(int t, int k, int ls[], int szls, int expr) {
    int act = chooseBestSum(t, k, ls, szls);
    if (act != expr)
        printf("Expected %d, got %d\n", expr, act);
    cr_assert_eq(act, expr, "");
}

Test(best_travel_test_suite, ShouldPassAllTheTestsProvided
) {
    {
        int ts[5] = {50, 55, 56, 57, 58};
        dotest(163, 3, ts, 5, 163);
    }
    {
        int ts[1] = {50};
        dotest(163, 3, ts, 1, -1);
    }
}
