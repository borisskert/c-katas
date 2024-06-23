enum game_state {
    NOT_FINISHED = -1, DRAW = 0, X_WON = 1, O_WON = 2
};
typedef enum game_state game_state;

enum square {
    EMPTY = 0, X = 1, O = 2
};
typedef enum square square;

/**
 * https://www.codewars.com/kata/525caa5c1bf619d28c000335/train/c
 */
game_state check_game_state(const square board[3][3]);

static game_state winner_of_rows(const square board[3][3]);

static game_state winner_of_columns(const square board[3][3]);

static game_state winner_of_diagonals(const square board[3][3]);

game_state check_game_state(const square board[3][3]) {
    game_state winner = DRAW;

    game_state row_winner = winner_of_rows(board);
    if (row_winner == X || row_winner == O) {
        return row_winner;
    }
    winner |= row_winner;

    game_state column_winner = winner_of_columns(board);
    if (column_winner == X || column_winner == O) {
        return column_winner;
    }
    winner |= column_winner;

    game_state diagonal_winner = winner_of_diagonals(board);
    if (diagonal_winner == X || diagonal_winner == O) {
        return diagonal_winner;
    }
    winner |= diagonal_winner;

    return winner;
}

static game_state winner_of(const square row_column_or_diagonal[3]);

static game_state winner_of(const square row_column_or_diagonal[3]) {
    game_state winner = (game_state) row_column_or_diagonal[0];

    if (winner == EMPTY) {
        return NOT_FINISHED;
    }

    for (int i = 1; i < 3; i++) {
        if (row_column_or_diagonal[i] == EMPTY) {
            return NOT_FINISHED;
        }

        if ((game_state) row_column_or_diagonal[i] != winner) {
            winner = DRAW;
        }
    }

    return winner;
}

static game_state winner_of_rows(const square board[3][3]) {
    game_state winner = DRAW;

    for (int i = 0; i < 3; i++) {
        game_state row_winner = winner_of(board[i]);

        if (row_winner == X || row_winner == O) {
            return row_winner;
        }

        winner |= row_winner;
    }

    return winner;
}

static game_state winner_of_columns(const square board[3][3]) {
    game_state winner = DRAW;

    for (int i = 0; i < 3; i++) {
        game_state column_winner = winner_of((square[3]) {board[0][i], board[1][i], board[2][i]});

        if (column_winner == X || column_winner == O) {
            return column_winner;
        }

        winner |= column_winner;
    }

    return winner;
}

static game_state winner_of_diagonals(const square board[3][3]) {
    game_state winner = DRAW;

    game_state diagonal_winner = winner_of((square[3]) {board[0][0], board[1][1], board[2][2]});
    if (diagonal_winner == X || diagonal_winner == O) {
        return diagonal_winner;
    }
    winner |= diagonal_winner;

    diagonal_winner = winner_of((square[3]) {board[0][2], board[1][1], board[2][0]});
    if (diagonal_winner == X || diagonal_winner == O) {
        return diagonal_winner;
    }

    return winner | diagonal_winner;
}
