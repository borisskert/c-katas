#include <string.h>
#include <stdio.h>

/**
 * https://www.codewars.com/kata/5839c48f0cf94640a20001d3/train/c
 */
void land_perimeter(size_t rows, size_t cols, const char land[rows][cols], char *result) {
    int perimeter = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (land[i][j] == 'X') {
                if (i == 0 || land[i - 1][j] == 'O') perimeter++;
                if (i == rows - 1 || land[i + 1][j] == 'O') perimeter++;
                if (j == 0 || land[i][j - 1] == 'O') perimeter++;
                if (j == cols - 1 || land[i][j + 1] == 'O') perimeter++;
            }

    sprintf(result, "Total land perimeter: %d", perimeter);
}
