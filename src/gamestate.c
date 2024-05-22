#include "movements.h"
#include "gamestate.h"


/**
 * Finds the position of the current player's king
 * 
 * @param pieces Array of pieces on the board
 * @param current_player The player whose king's position is being searched
 * @param king_x Pointer to store the X-coordinate of the king
 * @param king_y Pointer to store the Y-coordinate of the king
 * @return 1 if the king is found, 0 otherwise
 */
int find_king_position(Piece *pieces, Player current_player, int *king_x, int *king_y) {
    for (int i = 0; i < 32; i++) {
        if (pieces[i].type == KING && pieces[i].player == current_player) {
            *king_x = pieces[i].position[0];
            *king_y = pieces[i].position[1];
            return 1;
        }
    }
    return 0;
}

/**
 * Determines if the player's king is in check
 * 
 * @param pieces Array of pieces on the board
 * @param king_x X-coordinate of the king
 * @param king_y Y-coordinate of the king
 * @param player Player whose king is being checked
 * @return 1 if the king is in check, 0 otherwise
 */
int is_check(Piece *pieces, int king_x, int king_y, Player player) {
    for (int i = 0; i < 32; i++) {
        Piece *piece = &pieces[i];
        if (piece->player != player && !piece->captured) {
            int difference_x = king_x - piece->position[0];
            int difference_y = king_y - piece->position[1];

            // Check if the piece can move to the king's position
            int valid = 0;
            switch (piece->type) {
                case PAWN:
                    valid = valid_move_pawn(difference_x, difference_y, piece->player, piece->position[1]) == 2;
                    break;
                case ROOK:
                    valid = valid_move_rook(difference_x, difference_y);
                    break;
                case KNIGHT:
                    valid = valid_move_knight(difference_x, difference_y);
                    break;
                case BISHOP:
                    valid = valid_move_bishop(difference_x, difference_y);
                    break;
                case QUEEN:
                    valid = valid_move_queen(difference_x, difference_y);
                    break;
                case KING:
                    valid = (abs(difference_x) <= 1 && abs(difference_y) <= 1);
                    break;
            }

            if (valid) {
                // If the piece can move to the king's position, check if the path is clear
                PathCheck check = { piece->position[0], piece->position[1], king_x, king_y, piece->player, pieces };
                int path_result = check_path_collision(&check);
                if (path_result == 0 || path_result == 3) return 1; // King is in check
            }
        }
    }
    return 0; // King is not in check
}


/**
 * Determines if the player's king is in checkmate.
 * 
 * @param pieces Array of pieces on the board
 * @param king_x X-coordinate of the king
 * @param king_y Y-coordinate of the king
 * @param player Player whose king is being checked
 * @return 1 if the king is in checkmate, 0 otherwise
 */
int is_checkmate(Piece *pieces, int king_x, int king_y, Player player) {
    const int king_moves[8][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    for (int i = 0; i < 8; i++) {
        int new_x = king_x + king_moves[i][0];
        int new_y = king_y + king_moves[i][1];

        // Check if the new position is within bounds
        if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
            // Temporarily move the king to the new position
            int original_x = king_x, original_y = king_y;
            king_x = new_x;
            king_y = new_y;

            // Check if the king is in check in the new position
            int check = is_check(pieces, king_x, king_y, player);
            if (!check) return 0; // If the king is not in check, it's not checkmate

            // Move the king back to the original position
            king_x = original_x;
            king_y = original_y;
        }
    }
    return 1; // King is in checkmate
}


GameState check_game_state(Piece *pieces, Player current_player) {
    int king_x, king_y;

    if (!find_king_position(pieces, current_player, &king_x, &king_y)) return GAME_CONTINUE;

    if (is_check(pieces, king_x, king_y, current_player)) {
        return is_checkmate(pieces, king_x, king_y, current_player) ? CHECKMATE : CHECK;
    }

    return GAME_CONTINUE;
}