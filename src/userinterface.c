#include <stdlib.h>
#include <stdio.h>
#include "movements.h"

//Workaround for scanner
#ifdef _WIN32
#define SCANF_FUNC scanf_s
#else
#define SCANF_FUNC scanf
#endif


/**
 * Get the character representation for a piece
 * 
 * @param type The type of the piece
 * @param player The player who owns the piece
 * @return The character representation of the piece
 */
char get_piece_char(Figure type, Player player) {
    switch (type) {
        case KING: return (player == WHITE) ? 'K' : 'k';
        case QUEEN: return (player == WHITE) ? 'Q' : 'q';
        case ROOK: return (player == WHITE) ? 'R' : 'r';
        case BISHOP: return (player == WHITE) ? 'B' : 'b';
        case KNIGHT: return (player == WHITE) ? 'N' : 'n';
        case PAWN: return (player == WHITE) ? 'P' : 'p';
        default: return ' ';
    }
}


void print_metadata(Player current_player) {
    printf("Current Player: %s\n", current_player == WHITE ? "White" : "Black");
}


/**
 * Initialize the board with pieces from an empty space
 * 
 * @param pieces Array of pieces on the board
 * @param board The board to be initialized
 */
void init_board(Piece* pieces, char board[8][8]) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            board[y][x] = ' ';
        }
    }

    // Place pieces on the board
    for (int i = 0; i < 32; i++) {
        if (!pieces[i].captured) {
            int x = pieces[i].position[0];
            int y = pieces[i].position[1];
            board[y][x] = get_piece_char(pieces[i].type, pieces[i].player);
        }
    }
}


/**
 * Draw the chessboard with borders
 * 
 * @param board The board to be drawn
 */
void draw_board(char board[8][8]) {
    printf("   a   b   c   d   e   f   g   h\n");
    printf(" +---+---+---+---+---+---+---+---+\n");

    for (int y = 7; y >= 0; y--) {
        printf("%d|", y + 1);

        for (int x = 0; x < 8; x++) {
            printf(" %c |", board[y][x]);
        }

        printf(" %d\n", y + 1);
        printf(" +---+---+---+---+---+---+---+---+\n");
    }

    printf("   a   b   c   d   e   f   g   h\n");
}


/**
 * Select a piece at a given position
 * 
 * @param pieces Array of pieces on the board
 * @param x The x-coordinate of the position
 * @param y The y-coordinate of the position
 * @return Pointer to the piece at the position, or NULL if no piece is found
 */
Piece* select_piece(Piece *pieces, int x, int y) {
    for (int i = 0; i < 32; i++) {
        if (pieces[i].position[0] == x && pieces[i].position[1] == y && !pieces[i].captured) {
            return &pieces[i];
        }
    }
    return NULL;
}


/**
 * gets the needed coordinates from the stdin (macro usage for windows compatibility)
 * 
 * @param x pointer to the x-coordinate
 * @param y pointer to the y-coordinate
 * 
 * @todo fix SCANF_FUNC function missmatching
*/
void get_coordinates(int *x, int *y) {
    unsigned char col;
    int row;

    SCANF_FUNC(" %c%d", &col, &row);
    *x = col - 'a';
    *y = row - 1;
}

void handle_next_move(Piece pieces[], char board[8][8]) {
    int start_x, start_y, dest_x, dest_y;

    printf("Enter the piece to move (e.g., e2): ");
    get_coordinates(&start_x, &start_y);

    Piece* selected_piece = select_piece(pieces, start_x, start_y);
    if (selected_piece == NULL) {
        printf("No piece found at the specified location. Try again.\n");
        return;
    }

    printf("Enter the destination (e.g., e4): ");
    get_coordinates(&dest_x, &dest_y);

    int move_result = move_piece(selected_piece, dest_x, dest_y, pieces);

    if (move_result == 0) {
        printf("Move successful.\n");
    } else if (move_result == 1) {
        printf("Invalid move. Try again.\n");
    } else if (move_result == 2) {
        printf("Piece captured!\n");
    }
}


void setup_and_draw_board(Piece* pieces) {
    char board[8][8];
    init_board(pieces, board);
    draw_board(board);
}