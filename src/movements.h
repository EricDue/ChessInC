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

/**
 * Checks if the path ahead of the piece is valid or if a collision with an enemy piece will happen
 *
 * @param pointer to the struct with the relevant data for the check
 * @return 0 for clear path, 1 for no movement allowed, 2 for a collision and a captured piece
 */
int check_path_collision(PathCheck *check);

/**
 * executes the movement, first checks if movement of piece is valid and then if the path is valid
 *
 * @param takes a pointer to the piece, and the coordinates where the piece should move
 * @return returns 0 on successfull move, 1 if the path is blocked, 2 if an enemy could be captured, 3 if the move is invalid returns -1 if the piece is invalid 
 */
int move_piece(Piece *piece, int dest_x, int dest_y, Piece* pieces);

#endif
