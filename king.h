#ifndef __KING_H__
#define __KING_H__

struct Coord;

class King::public Piece {
	const int num_possible_moves = 10;
	Coord possible_moves[num_possible_moves];
	bool first_move;
public:
	void first_move_off();
	void first_move_on();
	bool get_first_move();
	std::vector<Coord> calc_valid_moves();
}

#endif
