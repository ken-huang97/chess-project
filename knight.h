#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"

class Knight(): public Piece{
	const int num_possible_moves = 8;
	Coord possible_moves [num_possible_moves];
public:
	Knight(Board *board, Coord posn, bool black, int name_value);
};

#endif
