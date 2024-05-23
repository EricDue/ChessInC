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
 * Checks for path collisions from start to end position
 * 
 * @param check PathCheck structure containing start and end positions, player, and pieces
 * @return 0 if path is clear, 1 if path is blocked, 2 if enemy piece can be captured, 3 if path encounters an enemy king
 */
int check_path_collision(PathCheck *check);


/**
 * Returns if the move for the queen is valid (horizontal, vertical, diagonal).
 * 
 * @param difference_x Difference in x-coordinate.
 * @param difference_y Difference in y-coordinate.
 * @return 1 if valid move, 0 otherwise.
 */
int valid_move_queen(int difference_x, int difference_y);


/**
 * Returns if the move for the rook is valid (horizontal or vertical)
 * 
 * @param difference_x Difference in x-coordinate
 * @param difference_y Difference in y-coordinate
 * @return 1 if valid move, 0 otherwise
 */
int valid_move_rook(int difference_x, int difference_y);


/**
 * Returns if the move for the bishop is valid (diagonal).
 * 
 * @param difference_x Difference in x-coordinate.
 * @param difference_y Difference in y-coordinate.
 * @return 1 if valid move, 0 otherwise
 */
int valid_move_bishop(int difference_x, int difference_y);


/**
 * Returns if the move for the knight is valid (L-shape).
 * 
 * @param difference_x Difference in x-coordinate
 * @param difference_y Difference in y-coordinate
 * @return 1 if valid move, 0 otherwise
 */
int valid_move_knight(int difference_x, int difference_y);


/**
 * Returns if the move for the pawn is valid (horizontal, diagonal on capture).
 * 
 * @param difference_x Difference in x-coordinate
 * @param difference_y Difference in y-coordinate
 * @param player Player who is moving
 * @param start_y Starting y-coordinate of the pawn
 * @return 1 if valid move, 2 if valid capture move, 0 otherwise
 */
int valid_move_pawn(int difference_x, int difference_y, Player player, int start_y);


/**
 * Moves the piece if the move is valid and path is clear.
 * 
 * @param piece Pointer to the piece
 * @param dest_x Destination x-coordinate
 * @param dest_y Destination y-coordinate
 * @param pieces Array of pieces on the board
 * @return 0 if move successful, 1 if path blocked, 2 if move successful with capture, 3 if invalid move.
 */
int move_piece(Piece *piece, int dest_x, int dest_y, Piece* pieces);

#endif
