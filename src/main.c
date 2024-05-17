#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//TODO enums & models in extra library
enum Figures {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

enum Players {
	WHITE,
	BLACK
};

int init_board(int chessboard[8][8]) {

	//TODO replace with unicode chess characters
	const char initialboard[8][8] = {
        {'r','n','b','q','k','b','n','r'},
        {'p','p','p','p','p','p','p','p'},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','Q','K','B','N','R'}
    };

	memcpy(chessboard, initialboard, sizeof (char) * 8 * 8);

	return 0;
}

int update_board() {
	//TODO update board on move
	return 0;
}

int draw_board() {
	int chessBoard[8][8];

	//TODO draw board on screen with metadata etc

	return 0;
}


int main() {
	
	return 0;
}
