#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
#include "coord.h"
#include <vector>

struct Coord;

class Rook : public Piece {
	bool first_move;
public:
	std::vector<Coord> calculateValidMoves();
	bool get_first_move();
}
