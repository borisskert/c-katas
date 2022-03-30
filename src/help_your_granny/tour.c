#include <stdlib.h>
#include <string.h>
#include <math.h>

struct friends {
    char **array;
    size_t size;
};

struct friendTowns {
    char **array;
    size_t size;
};

struct townDistances {
    char **array;
    size_t size;
};

struct distances {
    double *array;
    size_t size;
};

void filterFriendTowns(struct friendTowns *, struct friends);

struct distances extractDistances(struct townDistances townDistances, struct friendTowns friendTowns);

double grannysDistance(struct distances distances);

/**
 * https://www.codewars.com/kata/5536a85b6ed4ee5a78000035/train/c
 * @param arrFriends array of friends (example: { "A1", "A2", "A3", "A4", "A5" })
 * @param szArrFriends size of arrFriends (example: 5)
 * @param ftwns array of friends-towns (example: {"A1", "X1", "A2", "X2", "A3", "X3", "A4", "X4"})
 * @param townsDist array of town-distance (example: {"X1", "100.0", "X2", "200.0", "X3", "250.0", "X4", "300.0"})
 * @param szFTwns size of ftwns and townsDist (example: 8)
 * @return Granny's approximately the distance to travel
 */
int tour(char **arrFriends, int szArrFriends, char **ftwns, char **townsDist, int szFTwns) {
    struct friends friends;
    friends.array = arrFriends;
    friends.size = szArrFriends;

    struct friendTowns friendTowns;
    friendTowns.array = ftwns;
    friendTowns.size = szFTwns;

    struct townDistances townDistances;
    townDistances.array = townsDist;
    townDistances.size = szFTwns;

    filterFriendTowns(&friendTowns, friends);
    struct distances distances = extractDistances(townDistances, friendTowns);

    int distance = (int) grannysDistance(distances);
    free(distances.array);

    return distance;
}

double oppositeLeg(const double a, const double c) {
    return sqrt(c * c - a * a);
}

double grannysDistance(const struct distances distances) {
    double distance = distances.array[0];

    for (unsigned int index = 1; index < distances.size; index++) {
        double a = distances.array[index - 1];
        double c = distances.array[index];

        double b = oppositeLeg(a, c);

        distance += b;
    }

    distance += distances.array[distances.size - 1];

    return distance;
}

char *search(char **keyValuePairs, const size_t size, const char *key) {
    for (unsigned int index = 0; index < size; index += 2) {
        if (strcmp(keyValuePairs[index], key) == 0) {
            return keyValuePairs[index + 1];
        }
    }

    return NULL;
}

void filterFriendTowns(struct friendTowns *friendTowns, const struct friends friends) {
    unsigned int townIndex = 0;

    for (unsigned int index = 0; index < friends.size; index++) {
        char *friend = friends.array[index];
        char *town = search(friendTowns->array, friendTowns->size, friend);

        if (town != NULL) {
            friendTowns->array[townIndex] = town;
            townIndex++;
        }
    }

    friendTowns->size = townIndex;
}

struct distances extractDistances(const struct townDistances townDistances, const struct friendTowns friendTowns) {
    struct distances distances;
    distances.array = malloc(sizeof(double) * friendTowns.size);

    unsigned int distanceIndex = 0;

    for (unsigned int index = 0; index < friendTowns.size; index++) {
        char *town = friendTowns.array[index];

        char *distanceValue = search(townDistances.array, townDistances.size, town);
        if (distanceValue != NULL) {
            double distance = atof(distanceValue);
            distances.array[distanceIndex++] = distance;
        }
    }

    distances.size = distanceIndex;

    return distances;
}
