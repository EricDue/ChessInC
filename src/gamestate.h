#ifndef GAMESTATE
#define GAMESTATE

#include "chess.h"

typedef enum {
    GAME_CONTINUE,
    CHECK,
    CHECKMATE
} GameState;

/**
 * Determines the current state of the game for the current player.
 * 
 * @param pieces Array of pieces on the board
 * @param current_player The player whose game state is being checked
 * @return CHECKMATE if the player is in checkmate, CHECK if in check, GAME_CONTINUE otherwise
 */
GameState check_game_state(Piece *pieces, Player current_player);

#endif