#ifndef __BISHOP_H__
#define __BISHOP_H__

struct Coord;

class Bishop : public Piece {
public:
	std::vector<Coord> calc_valid_moves();
}

#endif
