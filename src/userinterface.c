#include <stdlib.h>
#include <stdio.h>
#include "chess.h"
#include "movements.h"

// Function to get the character representation for a piece
char get_piece_char(Figure type, Player player) {
    switch (type) {
        case KING:
            return (player == WHITE) ? 'K' : 'k';
        case QUEEN:
            return (player == WHITE) ? 'Q' : 'q';
        case ROOK:
            return (player == WHITE) ? 'R' : 'r';
        case BISHOP:
            return (player == WHITE) ? 'B' : 'b';
        case KNIGHT:
            return (player == WHITE) ? 'N' : 'n';
        case PAWN:
            return (player == WHITE) ? 'P' : 'p';
		default:
            return ' ';
    }
}
void print_metadata(Player current_player) {
    printf("Current Player: %s\n", current_player == WHITE ? "White" : "Black");
}


// Function to initialize the board with pieces
void init_board(Piece* pieces, char board[8][8]) {
    // Initialize the board with empty spaces
	int y;
    for (y = 0; y < 8; y++) {
		int x;
        for (x = 0; x < 8; x++) {
            board[y][x] = ' ';
        }
    }

    // Place pieces on the board
	int i;
    for (i = 0; i < 32; i++) {
        if (!pieces[i].captured) {
            int x = pieces[i].position[0];
            int y = pieces[i].position[1];
            board[y][x] = get_piece_char(pieces[i].type, pieces[i].player);
        }
    }
}

// Function to draw the chessboard with borders
void draw_board(char board[8][8]) {
    // Draw the top border with column labels
    printf("   a   b   c   d   e   f   g   h\n");
    printf(" +---+---+---+---+---+---+---+---+\n");

	int y;
    for (y = 7; y >= 0; y--) {
        // Print row number and left border
        printf("%d|", y + 1);

        // Print row pieces and borders between them
		int x;
        for (x = 0; x < 8; x++) {
            printf(" %c |", board[y][x]);
        }

        // Print row number on the right side
        printf(" %d\n", y + 1);

        // Print bottom border of the row
        printf(" +---+---+---+---+---+---+---+---+\n");
    }

    // Draw the bottom border with column labels
    printf("   a   b   c   d   e   f   g   h\n");
}

Piece* select_piece(Piece *pieces, int x, int y) {
    for (int i = 0; i < 32; i++) {
        if (pieces[i].position[0] == x && pieces[i].position[1] == y && pieces[i].captured == 0) {
            return &pieces[i];
        }
    }
    return NULL; // Return NULL if no piece is found
}

void handle_next_move(Piece pieces[], int num_pieces, char board[8][8]) {
    int start_x, start_y, dest_x, dest_y;
    char start_col, dest_col;
    int start_row, dest_row;

    printf("Enter the piece to move: ");
    scanf(" %c%d", &start_col, &start_row);
    start_x = start_col - 'a';
    start_y = start_row - 1;

    // Select the piece
    Piece* selected_piece = select_piece(pieces, start_x, start_y);
    if (selected_piece == NULL) {
        printf("No piece found at the specified location. Try again.\n");
        return;
    }

    // Ask the user for the destination
    printf("Enter the destination: ");
    scanf(" %c%d", &dest_col, &dest_row);
    dest_x = dest_col - 'a';
    dest_y = dest_row - 1;

    // Attempt to move the piece
    int move_result = move_piece(selected_piece, dest_x, dest_y, pieces);

    // Handle the result of the move
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
