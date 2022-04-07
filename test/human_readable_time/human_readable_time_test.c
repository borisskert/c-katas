#include <criterion/criterion.h>
#include <stdio.h>

char *human_readable_time(unsigned seconds, char *time_string);

static void do_test (unsigned seconds, const char *expected) {
    char result[100];
    char *act = human_readable_time(seconds, result);

    cr_assert_eq(result, act); // expect to be the same reference

    if (strcmp(act, expected) != 0)
        printf("scale. Error. Expected \n%s\n but got \n%s\n", expected, act);

    cr_assert_str_eq(act, expected, "");
    act = NULL;
}

Test(tests_suite, sample_tests) {
    do_test(0, "00:00:00");
    do_test(59, "00:00:59");
    do_test(60, "00:01:00");
    do_test(90, "00:01:30");
    do_test(3599, "00:59:59");
    do_test(3600, "01:00:00");
    do_test(45296, "12:34:56");
    do_test(86399, "23:59:59");
    do_test(86400, "24:00:00");
    do_test(359999, "99:59:59");
}
