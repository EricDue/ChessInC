#ifndef MAIN
#define MAIN

#include "chess.h"

/**
 * inits the Piece's for the board, allocates memory from the Heap 
 * 
 * @return new Pieces array
 * 
 * @warning the pieces need to be freed later
*/
Piece* init_pieces();


/**
 * free's the allocated memory of the Piece's
 * 
 * @param pieces pointer to the Piece's array
*/
void cleanup_board(Piece *pieces);


/**
 * declaration of the main game loop
 * 
 * @param pieces pointer to the Piece's array
*/
void main_gameloop(Piece *pieces);


#endif
