#include <vector>
#include "bishop.h"
#include "coord.h"
#include "board.h"

Bishop::Bishop(Board *board, Coord posn, bool black, int name_value): Piece{board, posn, black, name_value} {}

std::vector<Coord> Bishop::calculateValidMoves() {
	std::vector<Coord> valid;
	int x, y;
	if (is_pinned() == -1) {
		x = posn.x;
		y = posn.y;
		while (x > 0 && y > 0) {
			x--;
			y--;
			Piece* temp = board->get_piece(Coord(x,y));
			if (temp == nullptr) {
				valid.push_back(Coord(x,y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(x,y));
				break;
			}
			else break;
		}
		x = posn.x;
		y = posn.y;
		while (x > 0 && y < 7) {
			x--;
			y++;
			Piece* temp = board->get_piece(Coord(x,y));
			if (temp == nullptr) {
				valid.push_back(Coord(x,y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(x,y));
				break;
			}
			else break;
		}
		x = posn.x;
		y = posn.y;
		while (x < 7 && y > 0) {
			x++;
			y--;
			Piece* temp = board->get_piece(Coord(x,y));
			if (temp == nullptr) {
				valid.push_back(Coord(x,y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(x,y));
				break;
			}
			else break;
		}
		x = posn.x;
		y = posn.y;
		while (x < 7 && y < 7) {
			x++;
			y++;
			Piece* temp = board->get_piece(Coord(x,y));
			if (temp == nullptr) {
				valid.push_back(Coord(x,y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(x,y));
				break;
			}
			else break;
		}
	}
	if (is_pinned == 1) {
		x = posn.x;
		y = posn.y;
		while (x > 0 && y > 0) {
			x--;
			y--;
			Piece* temp = board->get_piece(Coord(x,y));
			if (temp == nullptr) {
				valid.push_back(Coord(x,y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(x,y));
				break;
			}
			else break;
		}
		x = posn.x;
		y = posn.y;
		while (x < 7 && y < 7) {
			x++;
			y++;
			Piece* temp = board->get_piece(Coord(x,y));
			if (temp == nullptr) {
				valid.push_back(Coord(x,y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(x,y));
				break;
			}
			else break;
		}
	}
	if (is_pinned == 3) {
		x = posn.x;
		y = posn.y;
		while (x < 7 && y > 0) {
			x++;
			y--;
			Piece* temp = board->get_piece(Coord(x,y));
			if (temp == nullptr) {
				valid.push_back(Coord(x,y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(x,y));
				break;
			}
			else break;
		}
		x = posn.x;
		y = posn.y;
		while (x > 0 && y < 7) {
			x--;
			y++;
			Piece* temp = board->get_piece(Coord(x,y));
			if (temp == nullptr) {
				valid.push_back(Coord(x,y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(x,y));
				break;
			}
			else break;
		}
	}
	return valid;
}
