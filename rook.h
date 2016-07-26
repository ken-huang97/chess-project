#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
#include "coord.h"
#include <vector>

class Rook : public Piece {
	bool first_move;
public:
	std::vector<Coord> calc_valid_moves();
	bool get_first_move();
}
