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
 * Checks if the movement is valid for the queen piece
 *
 * @param coordinates of the destinitation
 * @return 0 if move is valid, 1 if move is invalid for this piece
 */
int valid_move_queen(int dx, int dy);


/**
 * Checks if the movement is valid for the rook piece
 *
 * @param coordinates of the destinitation
 * @return 0 if move is valid, 1 if move is invalid for this piece
 */
int valid_move_rook(int dx, int dy);


/**
 * Checks if the movement is valid for the bishop piece
 *
 * @param coordinates of the destinitation
 * @return 0 if move is valid, 1 if move is invalid for this piece
 */
int valid_move_bishop(int dx, int dy);


/**
 * Checks if the movement is valid for the knight piece
 *
 * @param coordinates of the destinitation
 * @return 0 if move is valid, 1 if move is invalid for this piece
 */
int valid_move_knight(int dx, int dy);


/**
 * Checks if the movement is valid for the pawn piece
 *
 * @param coordinates of the destinitation, current player,  y coordinate of the current position
 * @return 0 if move is valid, 1 if move is invalid for this piece
 */
int valid_move_pawn(int dx, int dy, Player player, int start_y);

/**
 * executes the movement, first checks if movement of piece is valid and then if the path is valid
 *
 * @param takes a pointer to the piece, and the coordinates where the piece should move
 * @return returns 0 on successfull move, 1 if the path is blocked, 2 if an enemy could be captured, 3 if the move is invalid returns -1 if the piece is invalid 
 */
int move_piece(Piece *piece, int dest_x, int dest_y, Piece* pieces);

#endif
