#include <criterion/criterion.h>
#include <criterion/new/assert.h>

int score(const int dice[5]);

Test(Greed_is_Good_Tests, should_pass_all_the_tests_provided) {
    {
        const int dice[5] = {2, 3, 4, 6, 2};
        cr_assert(eq(int, score(dice), 0));
    }
    {
        const int dice[5] = {4, 4, 4, 3, 3};
        cr_assert(eq(int, score(dice), 400));
    }
    {
        const int dice[5] = {2, 4, 4, 5, 4};
        cr_assert(eq(int, score(dice), 450));
    }
}
