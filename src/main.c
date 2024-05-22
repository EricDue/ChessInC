#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "movements.h"
#include "gamestate.h"
#include "userinterface.h"
#include "main.h"


/**
 * sets the attributes of a new piece
 * @param piece pointer to the piece
 * @param id id of the piece
 * @param type type of the piece
 * @param player which color the piece has
 * @param x x-coordinate of the piece
 * @param y y-coordinate of the piece
*/
void set_piece(Piece *piece, int id, Figure type, Player player, int x, int y) {
    piece->id = id;
    piece->type = type;
    piece->player = player;
    piece->position[0] = x;
    piece->position[1] = y;
}


Piece* init_pieces() {
    Piece* pieces = (Piece*)malloc(32 * sizeof(Piece));
    if (pieces == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int id = 0;
    // White pieces
    set_piece(&pieces[id], id, ROOK, WHITE, 0, 0); id++;
    set_piece(&pieces[id], id, KNIGHT, WHITE, 1, 0); id++;
    set_piece(&pieces[id], id, BISHOP, WHITE, 2, 0); id++;
    set_piece(&pieces[id], id, QUEEN, WHITE, 3, 0); id++;
    set_piece(&pieces[id], id, KING, WHITE, 4, 0); id++;
    set_piece(&pieces[id], id, BISHOP, WHITE, 5, 0); id++;
    set_piece(&pieces[id], id, KNIGHT, WHITE, 6, 0); id++;
    set_piece(&pieces[id], id, ROOK, WHITE, 7, 0); id++;
    for (int i = 0; i < 8; i++) {
        set_piece(&pieces[id], id, PAWN, WHITE, i, 1); id++;
    }
    // Black pieces
    set_piece(&pieces[id], id, ROOK, BLACK, 0, 7); id++;
    set_piece(&pieces[id], id, KNIGHT, BLACK, 1, 7); id++;
    set_piece(&pieces[id], id, BISHOP, BLACK, 2, 7); id++;
    set_piece(&pieces[id], id, QUEEN, BLACK, 3, 7); id++;
    set_piece(&pieces[id], id, KING, BLACK, 4, 7); id++;
    set_piece(&pieces[id], id, BISHOP, BLACK, 5, 7); id++;
    set_piece(&pieces[id], id, KNIGHT, BLACK, 6, 7); id++;
    set_piece(&pieces[id], id, ROOK, BLACK, 7, 7); id++;
    for (int i = 0; i < 8; i++) {
        set_piece(&pieces[id], id, PAWN, BLACK, i, 6); id++;
    }

    return pieces;
}


void cleanup_board(Piece *pieces) {
    free(pieces);
}


void main_gameloop(Piece *pieces) {
    Player current_player = WHITE;
    GameState game_state = GAME_CONTINUE;

    while (game_state == GAME_CONTINUE) {
        print_metadata(current_player);
        setup_and_draw_board(pieces);

        handle_next_move(pieces, (char[8][8]){});
        game_state = check_game_state(pieces, current_player);

        if (game_state == CHECK) {
            printf("Check!\n");
        } else if (game_state == CHECKMATE) {
            printf("Checkmate! %s wins!\n", current_player == WHITE ? "Black" : "White");
            break;
        }

        current_player = (current_player == WHITE) ? BLACK : WHITE;
    }
}


int main() {
    printf("ChessInC - v0.0.1\n");

    Piece *pieces = init_pieces();
    main_gameloop(pieces);
    cleanup_board(pieces);

    return 0;
}