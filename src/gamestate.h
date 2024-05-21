#ifndef GAMESTATE

#define GAMESTATE

#include "chess.h"

typedef enum {
    GAME_CONTINUE,
    CHECK,
    CHECKMATE
} GameState;

/**
 * Checks the current state of the Game
 * 
 * @param takes a pointer to the pieces
 * @return returns current gamestate
*/
GameState check_game_state(Piece *pieces, Player current_player);

#endif