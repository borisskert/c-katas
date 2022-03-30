#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <criterion/criterion.h>

int tour(char **arrFriends, int szArrFriends, char **ftwns, char **townsDist, int szFTwns);

static void dotest(char **arrFriends, int szArrFriends, char **ftwns, char **townsDist, int szFTwns, int expr) {
    int act = tour(arrFriends, szArrFriends, ftwns, townsDist, szFTwns);
    if (act != expr)
        printf("Expected %d, got %d\n", expr, act);
    cr_assert_eq(act, expr, "");
}

Test(tour, ShouldPassAllTheTestsProvided) {
    {
        char *friends1[5] = {"A1", "A2", "A3", "A4", "A5"};
        char *fTowns1[8] = {"A1", "X1", "A2", "X2", "A3", "X3", "A4", "X4"};
        char *distTable1[8] = {"X1", "100.0", "X2", "200.0", "X3", "250.0", "X4", "300.0"};
        dotest(friends1, 5, fTowns1, distTable1, 8, 889);
    }
    {
        char *friends1[2] = {"B1", "B2"};
        char *fTowns1[10] = {"B1", "Y1", "B2", "Y2", "B3", "Y3", "B4", "Y4", "B5", "Y5"};
        char *distTable1[10] = {"Y1", "50.0", "Y2", "70.0", "Y3", "90.0", "Y4", "110.0", "Y5", "150.0"};
        dotest(friends1, 2, fTowns1, distTable1, 10, 168);
    }
}
