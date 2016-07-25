#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"

struct Coord;

class Rook : public Piece {
	bool first_move;
public:
	std::vector<Coord> calculateValidMoves();
	bool isFirstMove();
}
