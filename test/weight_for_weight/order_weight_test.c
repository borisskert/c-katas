#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <criterion/criterion.h>

char *orderWeight(const char *s);

static void dotest(const char *s, char *expr) {
    char *act = orderWeight(s);
    if (strcmp(act, expr) != 0)
        printf("scale. Error. Expected \n%s\n but got \n%s\n", expr, act);
    cr_assert_str_eq(act, expr, "");
    free(act);
    act = NULL;
}

Test(orderWeight, ShouldPassAllTheTestsProvided) {
    {
        dotest((const char *) "103 123 4444 99 2000", "2000 103 123 4444 99");
        dotest((const char *) "2000 10003 1234000 44444444 9999 11 11 22 123",
               "11 11 2000 10003 22 123 1234000 44444444 9999");
        dotest((const char *) "10003 1234000 44444444 9999 2000 123456789",
               "2000 10003 1234000 44444444 9999 123456789");
        dotest((const char *) "2000 11 44444444 9999 10003 123 11 1234000 22",
               "11 11 2000 10003 22 123 1234000 44444444 9999");
    }
}
