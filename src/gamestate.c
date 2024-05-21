#include "movements.h"
#include "gamestate.h"

int is_check(Piece *pieces, int king_x, int king_y, Player player) {
    for (int i = 0; i < 32; i++) {
        Piece *piece = &pieces[i];
        if (piece->player != player && !piece->captured) {
            int dx = king_x - piece->position[0];
            int dy = king_y - piece->position[1];

            // Check if the piece can move to the king's position
            int valid = 0;
            switch (piece->type) {
                case PAWN:
                    valid = valid_move_pawn(dx, dy, piece->player, piece->position[1]) == 2;
                    break;
                case ROOK:
                    valid = valid_move_rook(dx, dy);
                    break;
                case KNIGHT:
                    valid = valid_move_knight(dx, dy);
                    break;
                case BISHOP:
                    valid = valid_move_bishop(dx, dy);
                    break;
                case QUEEN:
                    valid = valid_move_queen(dx, dy);
                    break;
                case KING:
                    valid = (abs(dx) <= 1 && abs(dy) <= 1); // Adjacent squares
                    break;
            }

            if (valid) {
                // If the piece can move to the king's position, check if the path is clear
                PathCheck check = { piece->position[0], piece->position[1], king_x, king_y, piece->player, pieces };
                int path_result = check_path_collision(&check);
                if (path_result == 0 || path_result == 3) {
                    return 1; // King is in check
                }
            }
        }
    }
    return 0; // King is not in check
}


int is_checkmate(Piece *pieces, int king_x, int king_y, Player player) {
    const int king_moves[8][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int is_checkmate = 1; // Assume checkmate until proven otherwise

    for (int i = 0; i < 8 && is_checkmate; i++) {
        int new_x = king_x + king_moves[i][0];
        int new_y = king_y + king_moves[i][1];

        // Check if the new position is within bounds
        if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
            // Temporarily move the king to the new position
            int temp_x = king_x, temp_y = king_y;
            king_x = new_x;
            king_y = new_y;

            // Check if the king is in check
            int check = is_check(pieces, king_x, king_y, player);
            if (!check) {
                // If the king is not in check in this position, it's not in checkmate
                is_checkmate = 0;
            }

            // Move the king back to the original position
            king_x = temp_x;
            king_y = temp_y;
        }
    }

    return is_checkmate;
}

GameState check_game_state(Piece *pieces, Player current_player) {
    int king_x, king_y;

    // Find the current player's king
    for (int i = 0; i < 32; i++) {
        if (pieces[i].type == KING && pieces[i].player == current_player) {
            king_x = pieces[i].position[0];
            king_y = pieces[i].position[1];
            break;
        }
    }

    // Check if the current player's king is in check
    if (is_check(pieces, king_x, king_y, current_player)) {
        // Check if it is checkmate
        if (is_checkmate(pieces, king_x, king_y, current_player)) {
            return CHECKMATE;
        } else {
            return CHECK;
        }
    }

    // No check or checkmate
    return GAME_CONTINUE;
}