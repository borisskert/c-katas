#include <stdbool.h>

/**
 * https://www.codewars.com/kata/52774a314c2333f0a7000688/train/c
 * @param str_in a string containing parentheses
 * @return true if the order of the parentheses is valid, false if not
 */
bool validParentheses(const char *str_in) {
    int counter = 0;
    unsigned int index = 0;

    char c = str_in[index];

    while (c != '\0') {
        if (c == '(') {
            counter++;
        } else if (c == ')') {
            counter--;
        }

        if (counter < 0) {
            return false;
        }

        c = str_in[++index];
    }

    return counter == 0;
}
