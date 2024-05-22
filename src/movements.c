#include "movements.h"
#include <stdlib.h>

int calculate_step_direction(int start, int end) {
    int direction = end - start;

	if (direction == 0) {
		return 0;  // No movement in the x direction
	} else if (direction > 0) {
		return 1;  // Moving right
    }
	return -1; // Moving left
}

int check_path_collision(PathCheck *check) {

	// Calculate the differences in coordinates between the start and end positions
	int dx = check->end_x - check->start_x;
	int dy = check->end_y - check->start_y;

	// Determine the step direction for the x-coordinate
	int step_x;
	if (dx == 0) {
		step_x = 0;  // No movement in the x direction
	} else if (dx > 0) {
		step_x = 1;  // Moving right
	} else {
		step_x = -1; // Moving left
	}

	// Determine the step direction for the y-coordinate
	int step_y;
	if (dy == 0) {
		step_y = 0;  // No movement in the y direction
	} else if (dy > 0) {
		step_y = 1;  // Moving up
	} else {
		step_y = -1; // Moving down
	}

	// Initialize the current position to the next position from the start
	int x = check->start_x + step_x;
	int y = check->start_y + step_y;

    // Iterate through the path from start to end coordinates
    while (x != check->end_x || y != check->end_y) {
        // Check if any piece is located at the current position (x, y)
        for (int i = 0; i < 32; i++) {
            if (check->pieces[i].position[0] == x && check->pieces[i].position[1] == y) {
                if (check->pieces[i].player == check->player) {
                    return 1; // Path blocked
                } else {
                    if (check->pieces[i].type == KING) {
                        return 3; // Path encounters a king
                    }
					check->pieces[i].captured = 1;
                    return 2; // Piece can be captured
                }
            }
        }
        // Move to the next position in the path
        x += step_x;
        y += step_y;
    }
    return 0;  // Path is clear
}


int valid_move_queen(int dx, int dy) {
    return (dx == dy || dx == 0 || dy == 0);  // Valid for queen (horizontal, vertical, diagonal)
}

int valid_move_rook(int dx, int dy) {
    return (dx == 0 || dy == 0);  // Valid for rook (horizontal or vertical)
}

int valid_move_bishop(int dx, int dy) {
    return (abs(dx) == abs(dy));  // Valid for bishop (diagonal)
}

int valid_move_knight(int dx, int dy) {
    return ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2));  // Valid for knight (L-shape)
}

int valid_move_pawn(int dx, int dy, Player player, int start_y) {
    int direction = (player == WHITE) ? 1 : -1;

    if (dx == 0) {
        // Moving forward
        if (dy == direction || (start_y == 1 && player == WHITE && dy == 2) || (start_y == 6 && player == BLACK && dy == -2)) {
            return 1;  // Valid forward move
        }
    } else if (abs(dx) == 1 && dy == direction) {
        return 2;  // Valid capture move
    }
    
    return 0;  // Invalid move
}

int validate_move() {

}

int move_piece(Piece *piece, int dest_x, int dest_y, Piece* pieces) {
    int start_x = piece->position[0];
    int start_y = piece->position[1];
    int dx = dest_x - start_x;
    int dy = dest_y - start_y;

    int valid = 0;
    int move_type = 0;

    // Validate the movement based on the piece type
    switch (piece->type) {
        case QUEEN:
            valid = valid_move_queen(dx, dy);
            break;
        case ROOK:
            valid = valid_move_rook(dx, dy);
            break;
        case BISHOP:
            valid = valid_move_bishop(dx, dy);
            break;
        case KNIGHT:
            valid = valid_move_knight(dx, dy);
            break;
        case PAWN:
            move_type = valid_move_pawn(dx, dy, piece->player, start_y);
            valid = (move_type != 0);
            break;
        default:
            return -1;  // Invalid piece type
    }

    if (!valid) {
        return 3;  // Invalid move
    }
    // Check the path for obstacles or capture opportunities
    PathCheck check = { start_x, start_y, dest_x, dest_y, piece->player, pieces };
    int path_result = check_path_collision(&check);
    if (path_result == 1) {
        return 1;  // Path blocked
    }

    // Update the piece's position
    piece->position[0] = dest_x;
    piece->position[1] = dest_y;
    if (path_result == 2) {
        return 2;  // Move successful with capture
    }
    return 0;  // Move successful
}
