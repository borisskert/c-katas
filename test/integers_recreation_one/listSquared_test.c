#define _GNU_SOURCE // asprintf

#include <stdio.h>
#include <criterion/criterion.h>

typedef struct Pair Pair;
struct Pair {
    long long first;
    long long snd;
};

// sz number of pairs / Pair** arr will be freed
static char *array2StringData(Pair **arr, int sz);

extern Pair **listSquared(long long m, long long n, int *length);

static void dotest(long long m, long long n, char *sexpr) {
    int lg = 0;

    Pair **actual_pairs = listSquared(m, n, &lg);
    char *actual_as_string = array2StringData(actual_pairs, lg);

    cr_assert_str_eq(actual_as_string, sexpr, "Error. Expected %s but got %s\n", sexpr, actual_as_string);

    free(actual_as_string);
    actual_as_string = NULL;

    for (int i = 0; i < lg; i++) {
        free(actual_pairs[i]);
    }

    free(actual_pairs);
}

Test(listSquared, ShouldPassAllTheTestsProvided) {
    dotest(1, 250, "{{1, 1},{42, 2500},{246, 84100}}");
    dotest(42, 250, "{{42, 2500},{246, 84100}}");
    dotest(250, 500, "{{287, 84100}}");
    dotest(300, 600, "{}");
}

static char *array2StringData(Pair **arr, int sz) {
    if (sz == 0) return strdup("{}");

    char *buffers[sz];

    for (int i = 0; i < sz; i++) {
        char *buf;
        asprintf(&buf, "{%lld, %lld}", arr[i]->first, arr[i]->snd);
        buffers[i] = buf;
    }

    char *joined = buffers[0];
    for (int i = 1; i < sz; i++) {
        char *tmp = joined;
        asprintf(&joined, "%s,%s", tmp, buffers[i]);
        free(tmp);
        free(buffers[i]);
    }

    char *res;
    asprintf(&res, "{%s}", joined);
    free(joined);

    return res;
}
