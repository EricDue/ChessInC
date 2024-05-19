#ifndef CHESS

#define CHESS

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
