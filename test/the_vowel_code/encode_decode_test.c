#include <criterion/criterion.h>

char *encode(const char *);

char *decode(const char *);

Test(Sample_Tests, Tests) {
    cr_assert_str_eq(encode("hello"), "h2ll4");
    cr_assert_str_eq(encode("How are you today?"), "H4w 1r2 y45 t4d1y?");
    cr_assert_str_eq(encode("This is an encoding test."), "Th3s 3s 1n 2nc4d3ng t2st.");

    cr_assert_str_eq(decode("h2ll4"), "hello");
    cr_assert_str_eq(decode("H4w 1r2 y45 t4d1y?"), "How are you today?");
    cr_assert_str_eq(decode("Th3s 3s 1n 2nc4d3ng t2st."), "This is an encoding test.");
}
