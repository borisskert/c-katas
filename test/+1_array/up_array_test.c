#include <criterion/criterion.h>

#define ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))

extern int *up_array(const int *arr, unsigned *count);

static void do_test(const int *arr, unsigned count, const int *expected, unsigned expcount);

static void complete_test();

Test(sample_test, example_tests) {
    {
        int arr[] = {2, 3, 9},
                exp[] = {2, 4, 0};
        do_test(arr, ARRAY_COUNT(arr), exp, ARRAY_COUNT(exp));
    }
    {
        int arr[] = {4, 3, 2, 5},
                exp[] = {4, 3, 2, 6};
        do_test(arr, ARRAY_COUNT(arr), exp, ARRAY_COUNT(exp));
    }
    {
        int arr[] = {1, -9};
        do_test(arr, ARRAY_COUNT(arr), NULL, 0);
    }
    {
        int arr[] = {0, 4, 2},
                exp[] = {0, 4, 3};
        do_test(arr, ARRAY_COUNT(arr), exp, ARRAY_COUNT(exp));
    }
    {
        int arr[] = {9, 9, 9},
                exp[] = {1, 0, 0, 0};
        do_test(arr, ARRAY_COUNT(arr), exp, ARRAY_COUNT(exp));
    }
    {
        int arr[] = {9, 2, 2, 3, 3, 7, 2, 0, 3, 6, 8, 5, 4, 7, 7, 5, 8, 0, 7},
                exp[] = {9, 2, 2, 3, 3, 7, 2, 0, 3, 6, 8, 5, 4, 7, 7, 5, 8, 0, 8};
        do_test(arr, ARRAY_COUNT(arr), exp, ARRAY_COUNT(exp));
    }
    {
        int arr[] = {3, 7, -5, 8, 9, 9, 3, 0, 9, 8, 7, 5, 9};
        do_test(arr, ARRAY_COUNT(arr), NULL, 0);
    }
    {
        int arr[] = {5, 8, 0, 7, 7, 2, -2, 2, 3, 5, 2, 1, 3, 4, 3, 9, 2};
        do_test(arr, ARRAY_COUNT(arr), NULL, 0);
    }
    complete_test();
}

static void do_test(const int *arr, unsigned count, const int *expected, unsigned expcount) {
    unsigned count_ = count;
    int *got = up_array(arr, &count_);

    if (expected == NULL) {
        cr_assert_null(got, "Expected NULL");
        cr_assert_eq(count_, 0, "Expected count to be 0, but got %u", count_);
    } else {
        cr_assert_not_null(got, "Expected non-NULL");
        cr_assert_eq(count_, expcount, "Expected count to be %u, but got %u", expcount, count_);
        for (unsigned i = 0; i < expcount; i++) {
            cr_assert_eq(got[i], expected[i], "Expected %d at index %u, but got %d", expected[i], i, got[i]);
        }
        free(got);
    }
}

static void complete_test() {
    unsigned count = 0;
    int *got = up_array(NULL, &count);
    cr_assert_null(got, "Expected NULL");
    cr_assert_eq(count, 0, "Expected count to be 0");
    free(got);
}
