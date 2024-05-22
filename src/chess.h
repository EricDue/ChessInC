#ifndef CHESS
#define CHESS

// necessary enums & structs for the pieces
typedef enum Figure {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
} Figure;

typedef enum Player {
	WHITE,
	BLACK
} Player;

typedef struct Piece {
	int id;
    Player player;
	Figure type;
	int position[2];
	int captured;
} Piece;

#endif
