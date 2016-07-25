#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"

struct Coord;

class Bishop : public Piece {
public:
	std::vector<Coord> calculateValidMoves();
}
