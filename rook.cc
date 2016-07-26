#include <vector>
#include "rook.h"
#include "coord.h"
#include "board.h"

Rook::Rook(Board *board, Coord posn, bool black, int name_value): Piece{board, posn, black, name_value} {
	first_move = true;
}

bool Rook::get_first_move() {
	return first_move;
}

std::vector<Coord> Rook::calc_valid_moves() {
	std::vector<Coord> valid;
	if (is_pinned() == -1) {
		int i = posn.y;
		while (i > 0) {
			i--;
			Piece* temp = board->get_piece(Coord(posn.x, i));
			if (temp == nullptr) {
				valid.push_back(Coord(posn.x, i));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(posn.x, i));
				break;
			}
			else break;
		}
		i = posn.y;
		while (i < 7) {
			i++;
			Piece* temp = board->get_piece(Coord(posn.x, i));
			if (temp == nullptr) {
				valid.push_back(Coord(posn.x, i));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(posn.x, i));
				break;
			}
			else break;
		}	
		i = posn.x;
		while (i > 0) {
			i--;
			Piece* temp = board->get_piece(Coord(i, posn.y));
			if (temp == nullptr) {
			valid.push_back(Coord(i, posn.y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(i, posn.y));
				break;
			}
			else break;
		}
		i = posn.x
		while (i < 7) {
			i++;
			Piece* temp = board->get_piece(Coord(i, posn.y));
			if (temp == nullptr) {
				valid.push_back(Coord(i, posn.y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(i, posn.y));
				break;
			}
			else break;
		}	
	} else if (is_pinned() == 0) {
		int i = posn.y;
		while (i > 0) {
			i--;
			Piece* temp = board->get_piece(Coord(posn.x, i));
			if (temp == nullptr) {
				valid.push_back(Coord(posn.x, i));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(posn.x, i));
				break;
			}
			else break;
		}
		i = posn.y;
		while (i < 7) {
			i++;
			Piece* temp = board->get_piece(Coord(posn.x, i));
			if (temp == nullptr) {
				valid.push_back(Coord(posn.x, i));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(posn.x, i));
				break;
			}
			else break;
		}
	} else if (is_pinned() == 2) {
		i = posn.x;
		while (i > 0) {
			i--;
			Piece* temp = board->get_piece(Coord(i, posn.y));
			if (temp == nullptr) {
				valid.push_back(Coord(i, posn.y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(i, posn.y));
				break;
			}
			else break;
		}
		i = posn.x
		while (i < 7) {
			i++;
			Piece* temp = board->get_piece(Coord(i, posn.y));
			if (temp == nullptr) {
				valid.push_back(Coord(i, posn.y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(i, posn.y));
				break;
			}
			else break;
		}
	}
	return valid;
}
