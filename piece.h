#ifndef __PIECE_H__
#define __PIECE_H__

#include "coord.h"
#include <vector>

class Board;

class Piece {
	Board *board;
	Coord posn;
	bool black;
	int name_value;
	//pinned means it is currently protecting the king from being checked
	int is_pinned();
public:
	void update_posn(Coord new_posn);
	Coord get_posn();
	Bool is_black();
	int get_name_value();
	virtual std::vector<Coord> calc_valid_moves()=0;
}

#endif