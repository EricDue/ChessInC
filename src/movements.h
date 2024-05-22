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
