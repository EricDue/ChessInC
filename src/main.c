#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "chess.h"

void set_piece(Piece *piece,int id, Figure type, Player player, int x, int y) {
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

int main_gameloop() {
   //TODO game loop here 
   return 0;
}

int main() {
	Piece *pieces = init_pieces();


	
	cleanup_board(pieces);
	return 0;
}
