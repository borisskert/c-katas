#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

/**
 * https://www.codewars.com/kata/58e24788e24ddee28e000053/train/c
 */
void simple_assembler(size_t n, const char *const program[n], int registers[]);

struct machine {
    int instruction_pointer;
    int *registers;
};

struct instruction {
    char x[11];
    char y[11];

    void (*execute)(struct machine *machine, const char x[11], const char y[11]);
};

static void read_program(size_t n, const char *const program[], struct instruction instructions[]);

void simple_assembler(size_t n, const char *const program[n], int registers[]) {
    struct instruction instructions[n];

    read_program(n, program, instructions);

    struct machine machine = {0, registers};

    while (machine.instruction_pointer >= 0 && machine.instruction_pointer < n) {
        struct instruction instruction = instructions[machine.instruction_pointer];

        instruction.execute(&machine, instruction.x, instruction.y);

        machine.instruction_pointer++;
    }
}

static bool parseLong(const char *str, long *val);

static void move(struct machine *machine, const char x[10], const char y[10]) {
    long value = 0;
    int register_x = (int) x[0];

    if (parseLong(y, &value)) {
        machine->registers[register_x] = (int) value;
    } else {
        int register_y = (int) y[0];
        machine->registers[register_x] = machine->registers[register_y];
    }
}

static void increment(struct machine *machine, const char x[10], const char y[10]) {
    int register_x = (int) x[0];
    machine->registers[register_x] = machine->registers[register_x] + 1;
}

static void decrement(struct machine *machine, const char x[10], const char y[10]) {
    int register_x = (int) x[0];
    machine->registers[register_x] = machine->registers[register_x] - 1;
}

static void jump_not_zero(struct machine *machine, const char x[10], const char y[10]) {
    long valueX;

    if (parseLong(x, &valueX) == false) {
        int register_x = (int) x[0];
        valueX = machine->registers[register_x];
    }

    if (valueX != 0) {
        long valueY;

        if (parseLong(y, &valueY) == false) {
            int register_y = (int) y[0];
            valueY = machine->registers[register_y];
        }

        machine->instruction_pointer += (int) valueY - 1;
    }
}

static char **tokenize(const char *instruction_string);

static void read_program(size_t n, const char *const program[n], struct instruction instructions[n]) {
    for (int index = 0; index < n; index++) {
        const char *instruction_string = program[index];

        char **tokens = tokenize(instruction_string);

        if (strcmp(tokens[0], "mov") == 0) {
            struct instruction mov;

            strcpy(mov.x, tokens[1]);
            strcpy(mov.y, tokens[2]);
            mov.execute = &move;

            instructions[index] = mov;
        }

        if (strcmp(tokens[0], "inc") == 0) {
            struct instruction inc;

            strcpy(inc.x, tokens[1]);
            strcpy(inc.y, "");
            inc.execute = &increment;

            instructions[index] = inc;
        }

        if (strcmp(tokens[0], "dec") == 0) {
            struct instruction dec;

            strcpy(dec.x, tokens[1]);
            strcpy(dec.y, "");
            dec.execute = &decrement;

            instructions[index] = dec;
        }

        if (strcmp(tokens[0], "jnz") == 0) {
            struct instruction jnz;

            strcpy(jnz.x, tokens[1]);
            strcpy(jnz.y, tokens[2]);
            jnz.execute = &jump_not_zero;

            instructions[index] = jnz;
        }

        free(*tokens);
        free(tokens);
    }
}

/**
 * Split a string into n substrings by the specified delimiter
 * @param string the string to be split
 * @param n the substring count
 * @param delimiter the delimiter the string will be split up
 * @return an array of n strings
 */
static char **string_split(const char *string, size_t *n, const char *delimiter) {
    size_t maxLength = strlen(string);
    size_t maxByteLength = sizeof(char *) * maxLength;

    char **tokens = malloc(maxByteLength);

    /* Handle a copy into `strtok`, because the contents of this string are modified and broken into smaller strings (tokens). */
    char *copy = strdup(string);
    char *token = strtok(copy, delimiter);

    int actualLength = 0;
    while (token != NULL) {
        tokens[actualLength] = strdup(token);
        token = strtok(NULL, delimiter);
        actualLength = actualLength + 1;
    }

    free(copy);

    *n = actualLength;
    return tokens;
}

static char **tokenize(const char *instruction_string) {
    size_t wordsCount = 0;
    return string_split(instruction_string, &wordsCount, " ");
}

static bool parseLong(const char *str, long *val) {
    char *temp;
    bool rc = true;
    errno = 0;

    *val = strtol(str, &temp, 0);

    if (temp == str || *temp != '\0' ||
        ((*val == LONG_MIN || *val == LONG_MAX) && errno == ERANGE))
        rc = false;

    return rc;
}

// #againwhatlearned
// use `sscanf` to parse parts of a string
// int x, y;
// sscanf(program[i], "jnz %d %d", &x, &y) == 2
