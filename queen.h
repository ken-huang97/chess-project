#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"

struct Coord;

class Queen : public Piece {
public:
	std::vector<Coord> calc_valid_moves();
}
