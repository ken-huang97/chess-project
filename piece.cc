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

bool Piece::is_destroyed() {
	return destroyed;
}

int Piece::is_pinned() {
	//-1 for not protecting king
	//0 for above/below
	//1 for top-right/bottom-left
	//2 for right/left
	//3 for top-left/bottom-right
	
	
	//Check if it is protecting the king
	//check_piece is 3 or 4 depending on if we are on diagonal or horizontal/vertical
	// (3 is rook, 4 is bishop)
	//inc_x, inc_y, are in {-1, 0, 1}
	//inc_x, inc_y must lead to the king's position
	bool protects_king(int inc_x, int inc_y) {
		int x_count = inc_x;
		int y_count = inc_y;
		
		int enemy_check_piece = (abs(inc_x) + abs(inc_y) == 2) ? 4 : 3;
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
		if (inc_x == 1) {
			bound_1 = 8;
		}
		if (inc_y == 1) {
			bound_2 = 8;
		}
		while (posn.x + x_count != bound_1 && posn.y + y_count != bound_2) {
			Piece *temp = board->get_piece(posn.x + y_count, posn.y + y_count);
			if (temp==nullptr) {
				x_count += inc_x;
				y_count += inc_y;
			} else if (temp->black == this->black) {
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
	Coord kingPos = (this->black) ? board->black_pieces[0]->get_posn() : board->white_pieces[0]->get_posn();
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

bool Piece::is_safe() const{
	
	//For checking if there is an enemy that can capture this in a direction
	bool danger_in_direction(int inc_x, int inc_y) {
		int bound_x = (inc_x == 1) ? 8 : 0;
		int bound_y = (inc_y == 1) ? 8 : 0;
		int x_count = inc_x;
		int y_count = inc_y;
		
		//if there both inc are non-zero, it is diagonal, thus we check bishop
		//if only one is non-zero, it is horizontal/vertical, thus rook
		//if both are 0, this is invalid
		int enemy_check_piece = (abs(inc_x) + abs(inc_y) == 2) ? 4 : 3;
		while (posn.x + x < bound_x && posn.y + y < bound_y) {
			Piece *temp = board->get_piece(posn.x + x_count, posn.y + y_count);
			if (temp==nullptr) {
				x_count += inc_x;
				y_count += inc_y;
			//there is an ally in this direction
			} else if (temp->is_black == this->black) return false;
			//5 is queen
			} else if (temp->get_name_value() == enemy_check_piece || temp->get_name_value() == 5) {
				return true;
			//if there is an enemy piece, but it is not something that can capture this piece
			} else {
				//If it is 1 block away, check if enemy king can capture us
				if (abs(x) <= 1 && abs(y) <= 1) {
					if (temp->get_name_value() == 6) return true;
					//Check if white pawns can capture this piece
					if (temp->is_black()) {
						if (y == -1 && abs(x) == 1) {
							if (temp->get_name_value() == 1) return true;
						}
					//Check if black pawns can capture this piece
					} else {
						if (y == 1 && abs(x) == 1) {
							if (temp->get_name_value() == 1) return true;
						}
					}
				}
				//enemy piece that cannot capture this
				return false;
			}
		}
		//if no pieces in that direction
		return false;
	}
	
	
	//Special case for pawns
	if (name_value == 1 && en_passant) {
		if (posn.x + 1 <= 7) {
			Piece *temp = board->get_piece(posn.x - 1, posn.y);
			if (temp != nullptr) {
				if (temp->is_black() != this->black) {
					if (temp->get_name_value() == 1) {
						return false;
					}
				}
			}
		}
		if (posn.x - 1 >= 0) {
			Piece *temp = board->get_piece(posn.x - 1, posn.y);
			if (temp != nullptr) {
				if (temp->is_black() != this->black) {
					if (temp->get_name_value() == 1) {
						return false;
					}
				}
			}
		}
	}
	
	
	//If there is any danger in any of these directions, then it is not safe
	if (danger_in_direction(0, 1) 
		|| danger_in_direction(0, -1)
		|| danger_in_direction(1, 1)
		|| danger_in_direction(1, 0)
		|| danger_in_direction(1, -1)
		|| danger_in_direction(-1, 1)
		|| danger_in_direction(-1, 0)
		|| danger_in_direction(-1, -1)) {
		return false;	
	}
	
	
	//Check if this piece can be captured by a knight in a relative position
	bool enemy_knight(int x, int y) {
		if (posn.x + x <= 7 && posn.x + x >= 0) {
			if (posn.y + y <= 7 && posn.y + y >= 0) {
				Piece *temp = board->get_piece(posn.x + x, posn.y + y);
				if (temp != nullptr) {
					if (temp->is_black != this->black && temp->get_name_value() == 2) return true;
				}
			}
		}
		return false;
	}
	
	//Check if can be captured by a knight
	//if there is an enemy knight in any of the 8 possible spaces, it is not safe
	if (enemy_knight(1, 2)
		|| enemy_knight(2, 1)
		|| enemy_knight(-1, 2)
		|| enemy_knight(-2, 1)
		|| enemy_knight(1, -2)
		|| enemy_knight(2, -1)
		|| enemy_knight(-1, -2)
		|| enemy_knight(-2, -1)) {
		return false;
	}
	
	//no danger
	return true;
}

Piece::Piece(Board *board, Coord posn, bool black, int name_value): board{board}
	, posn{posn}, black{black}, name_value{name_value}, destroyed{false} {}
	
	
void Piece::destroyed_on(){
	destroyed = true;
}

void Piece::destroyed_off(){
	destroyed = false;
}
