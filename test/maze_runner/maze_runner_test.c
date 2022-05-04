#include <criterion/criterion.h>
#include <criterion/new/assert.h>

char *maze_runner(const int *maze, size_t n, const char *directions);

static void tester(const int *maze, size_t n, const char *directions, char *outcome);

Test(Maze_Runner_Tests, should_pass_all_the_tests_provided) {

#define N 7

    const int maze[N * N] = {1, 1, 1, 1, 1, 1, 1,
                             1, 0, 0, 0, 0, 0, 3,
                             1, 0, 1, 0, 1, 0, 1,
                             0, 0, 1, 0, 0, 0, 1,
                             1, 0, 1, 0, 1, 0, 1,
                             1, 0, 0, 0, 0, 0, 1,
                             1, 2, 1, 0, 1, 0, 1};

    //  maze is passed in as a 1-D int array with length n
    //  directions are passed in as a null-terninated string
    //  do not allocate memory, instead return a string literal

    {
        const char *directions = "NNNNNEEEEE";
        tester(maze, N, directions, "Finish");
    }
    {
        const char *directions = "NNNNNEESSEENNE";
        tester(maze, N, directions, "Finish");
    }
    {
        const char *directions = "NNNNNEEEEEWW";
        tester(maze, N, directions, "Finish");
    }
    {
        const char *directions = "NEEEE";
        tester(maze, N, directions, "Lost");
    }
    {
        const char *directions = "NNNWW";
        tester(maze, N, directions, "Dead");
    }
    {
        const char *directions = "NNNNNEESSSSSS";
        tester(maze, N, directions, "Dead");
    }
    {
        const int maze[10 * 10] = {1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
                                   1, 3, 1, 0, 1, 0, 0, 0, 0, 1,
                                   1, 0, 1, 0, 0, 0, 1, 1, 0, 1,
                                   1, 0, 1, 1, 1, 1, 1, 0, 0, 1,
                                   1, 0, 1, 0, 0, 0, 0, 0, 0, 1,
                                   1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
                                   1, 0, 1, 0, 1, 0, 0, 0, 0, 0,
                                   1, 0, 1, 0, 1, 0, 1, 1, 0, 1,
                                   1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
                                   1, 1, 1, 0, 1, 1, 1, 1, 2, 1};
        const char *directions = "NNNNNEESSSSSS";
        tester(maze, 10, directions, "Dead");
    }
}

void tester(const int *maze, size_t n, const char *directions, char *outcome) {
    char *actual = maze_runner(maze, n, directions);
    cr_assert(eq(str, actual, outcome));
}
