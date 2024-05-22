#include "movements.h"
#include <stdlib.h>


// Calculate step direction from start to end
/**
 * Calculates if movement is happening in a direction
 * 
 * @param start Starting position
 * @param end Ending position
 * @return 0 if no movement, 1 (right/up) or -1 (left/down) if movement
 */
int calculate_step_direction(int start, int end) {
    int direction = end - start;
    if (direction == 0) {
        return 0; 
    } else if (direction > 0) {
        return 1; 
    }
    return -1;
}

/**
 * Determines the step direction for both X and Y coordinates
 * Uses pointers to pass the step directions by reference
 * 
 * @param difference_x Difference in x-coordinate
 * @param difference_y Difference in y-coordinate
 * @param step_x Pointer to the step direction for x-coordinate
 * @param step_y Pointer to the step direction for y-coordinate
 */
void calculate_step_directions(int difference_x, int difference_y, int* step_x, int* step_y) {
    *step_x = calculate_step_direction(0, difference_x);
    *step_y = calculate_step_direction(0, difference_y);
}

/**
 * Checks if a piece blocks the path at the given position
 * 
 * @param pieces Array of pieces on the board
 * @param x Current x-coordinate
 * @param y Current y-coordinate
 * @param player Player who is moving
 * @return 0 if path is clear, 1 if path blocked by own piece, 2 if enemy piece can be captured, 3 if path encounters an enemy king
 */
int check_piece_at_position(Piece* pieces, int x, int y, int player) {
    for (int i = 0; i < 32; i++) {
        if (pieces[i].position[0] == x && pieces[i].position[1] == y) {
            if (pieces[i].player == player) {
                return 1; // Path blocked by own piece
            } else {
                if (pieces[i].type == KING) {
                    return 3; // Path encounters a king
                }
                pieces[i].captured = 1;
                return 2; // Piece can be captured
            }
        }
    }
    return 0; // Path is clear
}


int check_path_collision(PathCheck *check) {
    int difference_x = check->end_x - check->start_x;
    int difference_y = check->end_y - check->start_y;
    int step_x, step_y;
    calculate_step_directions(difference_x, difference_y, &step_x, &step_y);

    int current_x = check->start_x + step_x;
    int current_y = check->start_y + step_y;

    while (current_x != check->end_x || current_y != check->end_y) {
        int collision = check_piece_at_position(check->pieces, current_x, current_y, check->player);
        if (collision) return collision;
        current_x += step_x;
        current_y += step_y;
    }
    return 0;
}


/**
 * Returns if the move for the queen is valid (horizontal, vertical, diagonal).
 * 
 * @param difference_x Difference in x-coordinate.
 * @param difference_y Difference in y-coordinate.
 * @return 1 if valid move, 0 otherwise.
 */
int valid_move_queen(int difference_x, int difference_y) {
    return (difference_x == difference_y || difference_x == 0 || difference_y == 0);
}


/**
 * Returns if the move for the rook is valid (horizontal or vertical)
 * 
 * @param difference_x Difference in x-coordinate
 * @param difference_y Difference in y-coordinate
 * @return 1 if valid move, 0 otherwise
 */
int valid_move_rook(int difference_x, int difference_y) {
    return (difference_x == 0 || difference_y == 0);
}


/**
 * Returns if the move for the bishop is valid (diagonal).
 * 
 * @param difference_x Difference in x-coordinate.
 * @param difference_y Difference in y-coordinate.
 * @return 1 if valid move, 0 otherwise
 */
int valid_move_bishop(int difference_x, int difference_y) {
    return (abs(difference_x) == abs(difference_y));
}


/**
 * Returns if the move for the knight is valid (L-shape).
 * 
 * @param difference_x Difference in x-coordinate
 * @param difference_y Difference in y-coordinate
 * @return 1 if valid move, 0 otherwise
 */
int valid_move_knight(int difference_x, int difference_y) {
    return ((abs(difference_x) == 2 && abs(difference_y) == 1) || (abs(difference_x) == 1 && abs(difference_y) == 2));
}

/**
 * Returns if the move for the pawn is valid (horizontal, diagonal on capture).
 * 
 * @param difference_x Difference in x-coordinate
 * @param difference_y Difference in y-coordinate
 * @param player Player who is moving
 * @param start_y Starting y-coordinate of the pawn
 * @return 1 if valid move, 2 if valid capture move, 0 otherwise
 */
int valid_move_pawn(int difference_x, int difference_y, Player player, int start_y) {
    int direction = (player == WHITE) ? 1 : -1;
    if (difference_x == 0) {
        if (difference_y == direction || (start_y == 1 && player == WHITE && difference_y == 2) || (start_y == 6 && player == BLACK && difference_y == -2)) {
            return 1; // valid forward move
        }
    } else if (abs(difference_x) == 1 && difference_y == direction) {
        return 2; // valid capture move
    }
    return 0; // invalid move
}

/**
 * Creates a PathCheck struct.
 * 
 * @param piece Pointer to the piece
 * @param dest_x Destination x-coordinate
 * @param dest_y Destination y-coordinate
 * @param pieces Array of pieces on the board
 * @return New PathCheck struct
 */
PathCheck create_path_check(Piece *piece, int dest_x, int dest_y, Piece* pieces) {
    PathCheck check = {
        piece->position[0],
        piece->position[1],
        dest_x,
        dest_y,
        piece->player,
        pieces
    };
    return check;
}

/**
 * Validates the move based on the piece type.
 * 
 * @param piece Pointer to the piece
 * @param difference_x Difference in x-coordinate
 * @param difference_y Difference in y-coordinate
 * @return 1 if valid move, 0 otherwise.
 */
int validate_move(Piece* piece, int difference_x, int difference_y) {
    switch (piece->type) {
        case QUEEN:
            return valid_move_queen(difference_x, difference_y);
        case ROOK:
            return valid_move_rook(difference_x, difference_y);
        case BISHOP:
            return valid_move_bishop(difference_x, difference_y);
        case KNIGHT:
            return valid_move_knight(difference_x, difference_y);
        case PAWN:
            return valid_move_pawn(difference_x, difference_y, piece->player, piece->position[1]) != 0;
        default:
            return 0; // invalid piece type
    }
}


int move_piece(Piece *piece, int dest_x, int dest_y, Piece* pieces) {
    int start_x = piece->position[0];
    int start_y = piece->position[1];
    int difference_x = dest_x - start_x;
    int difference_y = dest_y - start_y;

    if (!validate_move(piece, difference_x, difference_y)) return 3; // invalid move

    PathCheck check = create_path_check(piece, dest_x, dest_y, pieces);
    int path_result = check_path_collision(&check);
    if (path_result == 1) return 1; // path blocked

    // Update the piece's position
    piece->position[0] = dest_x;
    piece->position[1] = dest_y;
    
    if (path_result == 2) return 2; // move successful with capture
    return 0; // move successful
}