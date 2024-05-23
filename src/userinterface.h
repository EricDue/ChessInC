#ifndef USERINTERFACE
#define USERINTERFACE

#include "chess.h"

/**
 * Print metadata about the current player
 * 
 * @param current_player The player whose turn it is
 */
void print_metadata(Player current_player);


/**
 * Setup and draw the board
 * 
 * @param pieces Array of pieces on the board
 */
void setup_and_draw_board(Piece* pieces);


/**
 * Handle the next move from the user
 * 
 * @param pieces Array of pieces on the board
 * @param num_pieces Number of pieces on the board
 * @param board The board
 */
void handle_next_move(Piece pieces[], char board[8][8]);

#endif