#include <criterion/criterion.h>
#include <criterion/new/assert.h>

int beeramid(double bonus, double price);

Test(beeramid, should_pass_some_fixed_tests) {
    cr_assert(eq(int, beeramid(1500, 2), 12));
    cr_assert(eq(int, beeramid(5000, 3), 16));
    cr_assert(eq(int, beeramid(3.0, 4.0), 0));
    cr_assert(eq(int, beeramid(10.0, 2.0), 2));
}
