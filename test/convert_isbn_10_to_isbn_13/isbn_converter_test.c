#include <criterion/criterion.h>
#include <criterion/new/assert.h>

char *ISBN_converter(char *ISBN_13, const char *ISBN_10);

static void do_test(const char *ISBN_10, const char *ISBN_13) {
    char actual_ISBN_13[18];
    cr_assert(eq(str, ISBN_converter(actual_ISBN_13, ISBN_10), (char *) ISBN_13));
}

Test(ISBN_converter_tests_suite, sample_tests) {
    do_test("1-85326-158-0", "978-1-85326-158-9");
    do_test("0-14-143951-3", "978-0-14-143951-8");
    do_test("0-02-346450-X", "978-0-02-346450-8");
    do_test("963-14-2164-3", "978-963-14-2164-4");
    do_test("1-7982-0894-6", "978-1-7982-0894-6");
}
//verliebt.verlobt.verhetratet<3
