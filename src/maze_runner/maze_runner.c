#include <stddef.h>
#include <string.h>

struct position {
    int x;
    int y;
};

static struct position find_start(const int *maze, size_t n);

static struct position move(struct position position, char direction);

static unsigned int position_to_index(struct position position, size_t n);

/**
 * https://www.codewars.com/kata/58663693b359c4a6560001d6/train/c
 * @param maze as one-dim array
 * @param n the line length
 * @param directions as char-array
 * @return "Dead", "Lost" or "Finish"
 */
char *maze_runner(const int *maze, size_t n, const char *directions) {
    struct position position = find_start(maze, n);

    for (unsigned int index = 0; index < strlen(directions); index++) {
        char direction = directions[index];
        position = move(position, direction);

        if (position.x < 0 || position.x >= n || position.y < 0 || position.y >= n) {
            return "Dead";
        }

        unsigned int mazeIndex = position_to_index(position, n);
        int field = maze[mazeIndex];

        if (field == 1) {
            return "Dead";
        } else if (field == 3) {
            return "Finish";
        }
    }

    return "Lost";
}

struct position index_to_position(unsigned int index, size_t n) {
    struct position position;

    position.y = index / n;
    position.x = index % n;

    return position;
}

unsigned int position_to_index(struct position position, size_t n) {
    return position.y * n + position.x;
}

struct position move(struct position position, char direction) {
    struct position result = position;

    if (direction == 'N') {
        result.y = position.y - 1;
    } else if (direction == 'S') {
        result.y = position.y + 1;
    } else if (direction == 'E') {
        result.x = position.x + 1;
    } else if (direction == 'W') {
        result.x = position.x - 1;
    }

    return result;
}

struct position find_start(const int *maze, size_t n) {
    struct position result;
    result.x = -1;
    result.y = -1;

    for (unsigned int index = 0; index < (n * n); index++) {
        int value = maze[index];

        if (value == 2) {
            result = index_to_position(index, n);
            break;
        }
    }

    return result;
}
