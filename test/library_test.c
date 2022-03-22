#include <criterion/criterion.h>

char *hello(void);

Test(library_example, ShouldPassAllTheTestsProvided) {
    {
        cr_assert_str_eq(hello(), "Hello, World!", "");
    }
}
