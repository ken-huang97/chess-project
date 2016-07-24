#ifndef __KING_H__
#define __KING_H__

struct Coord;

class King::public Piece {
	const int num_possible_moves = 10;
	Coord possible_moves[num_possible_moves];
	bool first_move;
}

#endif