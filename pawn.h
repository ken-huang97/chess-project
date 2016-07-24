#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"
struct Coord;

class Pawn(): public Piece{
	bool en_passant, first_move;
	const int num_possible_moves = 4;
	Coord possible_move [num_possible_moves];
	vector<bool> is_en_passant;
public:
	Pawn(Board *board, Coord posn, bool black, int name_value);
	void Promote(int name);
	void en_passant_off();
	void en_passant_on();
	bool get_en_passant();
	void first_move_off();
	void first_move_on();
	bool get_first_move();
	vector<Coord> calc_valid_moves();
	vector<bool> get_is_en_passant;
};

#endif
