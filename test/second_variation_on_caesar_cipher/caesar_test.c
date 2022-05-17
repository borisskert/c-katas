#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

static char *joinStringsStringArray(char *strings[], int count);

char **encode(char *string, int shift, int *lg);

char *decode(char **strings, int size);

void dotest1(char *u, int shift, char *expr) {
    int lg = 0;
    char **act = encode(u, shift, &lg);
    char *sact = joinStringsStringArray(act, lg);
    if (strcmp(sact, expr) != 0)
        printf("Error. Expected \n%s\n but got \n%s\n", expr, sact);
    cr_assert_str_eq(sact, expr, "");
    free(sact);
    sact = NULL;
    free(act);
    act = NULL;
}

void dotest2(char *u[], int sz, char *expr) {
    char *sact = decode(u, sz);
    char *su = joinStringsStringArray(u, sz);
    if (strcmp(sact, expr) != 0)
        printf("Error. Expected \n%s\n but got \n%s\n", expr, sact);
    cr_assert_str_eq(sact, expr, "");
    free(sact);
    sact = NULL;
    free(su);
    su = NULL;
}

Test(SecondVariationonCaesarCipher, ShouldPassAllTheTestsProvided) {
    {
        char *u = "I should have known that you would have a perfect answer for me!!!";
        char *sol = "{'ijJ tipvme ibw','f lopxo uibu z','pv xpvme ibwf ','b qfsgfdu botx','fs gps nf!!!'}";
        dotest1(u, 1, sol);
    }
    {
        char *u = "I should have known that you would have a perfect answer for me!!!";
        char *sol[5] = {"ijJ tipvme ibw", "f lopxo uibu z", "pv xpvme ibwf ", "b qfsgfdu botx", "fs gps nf!!!"};
        dotest2(sol, 5, u);
    }
    {
        char *u = "abcdefghjuty12";
        char *sol = "{'abbc','defg','hikv','uz12'}";
        dotest1(u, 1, sol);
    }
    {
        char *u = "I can reset without pain";
        char *sol[5] = {"imM ge", "r viwi", "x amxl", "syx te", "mr"};
        dotest2(sol, 5, u);
    }
}

char *joinStringsStringArray(char *strings[], int count) {
    char *result = malloc(sizeof(char *) * (count + 2) * 2);
    strcat(result, "{");

    int i;
    for (i = 0; i < count; ++i) {
        strcat(result, "'");
        strcat(result, strings[i]);
        strcat(result, "'");
        if (i != count - 1)
            strcat(result, ",");
    }

    strcat(result, "}");

    return result;
}
