#include <stddef.h>
#include <criterion/criterion.h>

enum {
    N = 128
};

#define ARR_LEN(array) (sizeof(array) / sizeof *(array))

extern void simple_assembler(size_t n, const char *const program[n], int registers[]);

#define fixed_test(program, registers) run_and_assert(ARR_LEN(program), program, registers)

static void run_and_assert(size_t n, const char *program[n], int expected[]) {
    int registers[N] = {0};
    simple_assembler(n, program, registers);

    for (int i = 0; i < N; i++) {
        cr_assert_eq(registers[i], expected[i], "Expected %d for %c, but got %d", expected[i], (char) i, registers[i]);
    }
}

Test(simple_assembler_tests_suite, sample_tests) {
    fixed_test( // move constant to register
            ((const char *[]) {"mov a 5"}),
            ((int[N]) {['a'] = 5}
            )
    );

    fixed_test( // copy register to register
            ((const char *[]) {"mov a 5", "mov b a"}),
            ((int[N]) {['a'] = 5, ['b'] = 5}
            )
    );

    fixed_test( // copy 0 to register
            ((const char *[]) {"mov b a"}),
            ((int[N]) {['b'] = 0}
            )
    );

    fixed_test( // increment register
            ((const char *[]) {"mov a 5", "inc a"}),
            ((int[N]) {['a'] = 6}
            )
    );

    fixed_test( // increment 0 register
            ((const char *[]) {"inc a"}),
            ((int[N]) {['a'] = 1}
            )
    );

    fixed_test( // decrement register
            ((const char *[]) {"mov a 5", "dec a"}),
            ((int[N]) {['a'] = 4}
            )
    );

    fixed_test( // decrement 0 register
            ((const char *[]) {"dec a"}),
            ((int[N]) {['a'] = -1}
            )
    );

    fixed_test( // jump if register is not 0
            ((const char *[]) {"mov a 5", "jnz a 2", "mov a 1"}),
            ((int[N]) {['a'] = 5}
            )
    );

    fixed_test( // do not jump if register is 0
            ((const char *[]) {"mov a 0", "jnz a 2", "mov a 1"}),
            ((int[N]) {['a'] = 1}
            )
    );

    fixed_test( // jump if constant is not 0
            ((const char *[]) {"mov a 5", "jnz 1 2", "mov a 1"}),
            ((int[N]) {['a'] = 5}
            )
    );

    fixed_test( // do not jump if constant is 0
            ((const char *[]) {"mov a 5", "jnz 0 2", "mov a 1"}),
            ((int[N]) {['a'] = 1}
            )
    );

    fixed_test(((const char *[])
            {"mov a 5", "inc a", "dec a", "dec a", "jnz a -1", "inc a"}), ((int[N])
            {['a'] = 1}
               ));
    fixed_test(((const char *[])
            {"mov a -10", "mov b a", "inc a", "dec b", "jnz a -2"}), ((int[N])
            {['a'] = 0, ['b'] = -20}
               ));
    fixed_test(((const char *[])
            {"mov a 1", "mov b 1", "mov c 0", "mov d 26", "jnz c 2", "jnz 1 5", "mov c 7", "inc d", "dec c", "jnz c -2",
             "mov c a", "inc a", "dec b", "jnz b -2", "mov b c", "dec d", "jnz d -6", "mov c 18", "mov d 11", "inc a",
             "dec d", "jnz d -2", "dec c", "jnz c -5"}), ((int[N])
            {['a'] = 318009, ['b'] = 196418, ['c'] = 0, ['d'] = 0}
               ));
    fixed_test(((const char *[])
            {"mov d 100", "dec d", "mov b d", "jnz b -2", "inc d", "mov a d", "jnz 5 10", "mov c a"}), ((int[N])
            {['d'] = 1, ['b'] = 0, ['a'] = 1}
               ));
    fixed_test(((const char *[])
            {"mov c 12", "mov b 0", "mov a 200", "dec a", "inc b", "jnz a -2", "dec c", "mov a b", "jnz c -5",
             "jnz 0 1", "mov c a"}), ((int[N])
            {['c'] = 409600, ['b'] = 409600, ['a'] = 409600}
               ));
}
