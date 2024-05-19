#ifndef MOVEMENTS

#define MOVEMENTS

#include "chess.h"

typedef struct {
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    Player player;
    Piece* pieces;
} PathCheck;

int check_path_collision(PathCheck *check);

int valid_move_queen(int dx, int dy);

int valid_move_rook(int dx, int dy);

int valid_move_bishop(int dx, int dy);

int valid_move_knight(int dx, int dy);


int valid_move_pawn(int dx, int dy, Player player, int start_y);

int move_piece(Piece *piece, int dest_x, int dest_y, Piece* pieces);

#endif
