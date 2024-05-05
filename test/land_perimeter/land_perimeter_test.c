#include <stddef.h>
#include <criterion/criterion.h>

void land_perimeter(size_t rows, size_t cols, const char land[rows][cols], char *result);

static void tester(size_t rows, size_t cols, const char land[rows][cols], char *expected) {
    char *result = malloc(100);
    land_perimeter(rows, cols, land, result);

    cr_assert_str_eq(result, expected, "*Actual*: \"%s\"\nExpected: \"%s\"", result, expected);
}

Test(land_perimeter_tests_suite, land_perimeter_sample_tests) {
    tester(10, 6, ((char[][6]) {
            "OXOOOX",
            "OXOXOO",
            "XXOOOX",
            "OXXXOO",
            "OOXOOX",
            "OXOOOO",
            "OOXOOX",
            "OOXOOO",
            "OXOOOO",
            "OXOOXX"
    }), "Total land perimeter: 60");

    tester(11, 5, ((char[][5]) {
            "OXOOO",
            "OOXXX",
            "OXXOO",
            "XOOOO",
            "XOOOO",
            "XXXOO",
            "XOXOO",
            "OOOXO",
            "OXOOX",
            "XOOOO",
            "OOOXO"
    }), "Total land perimeter: 52");

    tester(5, 8, ((char[][8]) {
            "XXXXXOOO",
            "OOXOOOOO",
            "OOOOOOXO",
            "XXXOOOXO",
            "OXOXXOOX"
    }), "Total land perimeter: 40");

    tester(7, 7, ((char[][7]) {
            "XOOOXOO",
            "OXOOOOO",
            "XOXOXOO",
            "OXOXXOO",
            "OOOOOXX",
            "OOOXOXX",
            "XXXXOXO"
    }), "Total land perimeter: 54");

    tester(7, 6, ((char[][6]) {
            "OOOOXO",
            "XOXOOX",
            "XXOXOX",
            "XOXOOO",
            "OOOOOO",
            "OOOXOO",
            "OOXXOO"
    }), "Total land perimeter: 40");

    tester(1, 1, ((char[][1]) {
            "X"
    }), "Total land perimeter: 4");
}
