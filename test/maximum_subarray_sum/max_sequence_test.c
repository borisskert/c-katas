#include <criterion/criterion.h>
#include <stddef.h>

int maxSequence(const int *array, size_t n);

Test(Sample_Tests, should_work_on_an_empty_array) {
    const int array[0] = {};
    int submitted = maxSequence(array, 0);
    int expected = 0;
    cr_assert_eq(expected, submitted, "Expected: %d  Submitted %d\n", expected, submitted);
}

Test(Sample_Tests, should_work_on_this_example) {
    const int array[9] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int submitted = maxSequence(array, 9);
    int expected = 6;
    cr_assert_eq(expected, submitted, "Expected: %d  Submitted %d\n", expected, submitted);
}
