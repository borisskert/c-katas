#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <criterion/criterion.h>

char *joinStringsStringArray(char *strings[], int count);

// arr: directions to reduce, sz: size of arr, lg size of returned array
// function result will be freed
char **dirReduc(char **array, int size, int *reducedSize);

// dotest compares your results and test results by way of strings
void dotest(char **arr, int sz, char *expr) {
    int lg = -1;
    char **act = dirReduc(arr, sz, &lg);
    char *sact = joinStringsStringArray(act, lg);
    cr_assert_str_eq(sact, expr, "");
    if (strcmp(sact, "{}") != 0) {
        free(sact);
        sact = NULL;
    }
    free(act);
    act = NULL;
}

char *joinStringsStringArray(char *strings[], int count) {
    char *result = malloc(sizeof(char*) * count * 2);
    strcpy(result, "{");

    int i;
    for (i = 0; i < count; ++i) {
        strcat(result, strings[i]);
        if (i != count - 1)
            strcat(result, ", ");
    }

    strcat(result, "}");

    return result;
}

Test(dirReduc, ShouldPassAllTheTestsProvided) {
    {
        char *d1[7] = {"NORTH", "SOUTH", "SOUTH", "EAST", "WEST", "NORTH", "WEST"};
        dotest(d1, 7, "{WEST}");
    }
    {
        char *d1[4] = {"NORTH", "WEST", "SOUTH", "EAST"};
        dotest(d1, 4, "{NORTH, WEST, SOUTH, EAST}");
    }
    {
        char *d1[10] = {"NORTH", "WEST", "SOUTH", "EAST", "NORTH", "WEST", "SOUTH", "EAST", "SOUTH", "NORTH"};
        dotest(d1, 10, "{NORTH, WEST, SOUTH, EAST, NORTH, WEST, SOUTH, EAST}");
    }
    {
        char *d1[4] = {"NORTH", "SOUTH", "WEST", "EAST"};
        dotest(d1, 4, "{}");
    }
    {
        char *d1[0] = {};
        dotest(d1, 0, "{}");
    }
}
