#include "piece.h"
#include "coord.h"
#include "board.h"
#include <cmath>

void Piece::update_posn(Coord new_posn) {
	posn = new_posn;
}

Coord Piece::get_Posn() {
	return posn;
}

bool Piece::is_black() {
	return black;
}

int Piece::get_name_value() {
	return name_value;
}

int Piece::is_pinned() {
	//-1 for not protecting king
	//0 for infinity (slope)
	//1 for 1
	//2 for 0
	//3 for -1
	
	
	//Check if it is protecting the king
	//check_piece is 3 or 4 depending on if we are on diagonal or horizontal/vertical
	// (3 is rook, 4 is bishop)
	//inc_x, inc_y, are in {-1, 0, 1}
	//inc_x, inc_y must lead to the king's position
	bool protects_king(int inc_x, int inc_y, const int check_piece) {
		int x_count = inc_x;
		int y_count = inc_y;
		while (true) {
			Piece *temp = board->get_piece(posn.x + x_count, posn.y + y_count);
			if (temp==nullptr) {
				x_count += inc_x;
				y_count += inc_y;
			//if there is nothing between it and its allied king
			//*don't need to check if it is an enemy king because that would be move after check which is impossible
			} else if (temp->get_name_value() == 6) {
				break;
			//if there is a piece between it and its king (not the only protector)
			} else {
				return false;
			}
		}
		
		//only runs if nothing between it and its king

		//flip direction
		inc_x *= -1;
		inc_y *= -1;
		
		x_count = inc_x;
		y_count = inc_y;
		
		int bound_1 = 0;
		int bound_2 = 0;
		if (inc_x == -1) {
			bound_1 = 0;
		} else if (inc_x == 1) {
			bound_1 = 8;
		}
		if (inc_y == -1) {
			bound_2 = 0;
		} else if (inc_y == 1) {
			bound_2 = 8;
		}
		while (posn.x + x_count != bound_1 && posn.y + y_count != bound_2) {
			Piece *temp = board->get_piece(posn.x + y_count, posn.y + y_count);
			if (temp==nullptr) {
				x_count += inc_x;
				y_count += inc_y;
			} else if (temp->black == this.black) {
				return false;
			//5 is queen
			//we only need to check check_piece and queen because they are the only ones that 
			//can possibly check the king when something moves out of the way
			} else if (temp->get_name_value() == check_piece || temp->get_name_value == 5) {
				return true;
			//if there is an ally opposite of the king
			} else {
				return false;
			}
		}
		//if there are no pieces opposite of the king
		return false;
	}
	
	//black_pieces[0] is the black king, etc.
	Coord kingPos = (this.black) ? board->black_pieces[0]->get_posn() : board->white_pieces[0]->get_posn();
	//king on same x axis
	if (kingPos.x == posn.x) {
		//king is above
		if (kingPos.y > posn.y) {
			if (protects_king(0, 1, 3)) return 0;
			return -1;
		//else king is below this piece
		} else {
			if (protects_king(0, -1, 3)) return 0;
			return -1;
		}
	}
	//king is on same y axis
	if (kingPos.y == posn.y) {
		//king is to the right
		if (kingPos.x > posn.x) {
			if (protects_king(1, 0, 3)) return 2;
			return -1;
		//king is to the left
		} else {
			if (protects_king(-1, 0, 3)) return 2;
			return -1;
		}
	//if the king is in a diagonal from this piece
	if (abs(posn.x - kingPos.x) == abs(posn.y - kingPos.y)) {
		if (kingPos.x < posn.x) {
			//king is bottom and left
			if (kingPos.y < posn.y) {
				if (protects_king(-1, -1, 4)) return 1;
				return -1;
			}
			//else king is above and left
			if (protects_king(-1, 1, 3)) return 3;
			return -1;
		} else {
			//king is bottom and right
			if (kingPos.y < posn.y) {
				if (protects_king(1, -1, 4)) return 3;
				return -1;
			}
			//else king is above and right
			if (protects_king(1, 1, 3)) return 1;
			return -1;
		}
	}
	
	//if king is not in a straight line from this piece
	return -1;
}