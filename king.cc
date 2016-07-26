#include "coord.h"
#include "moving.h"
#include "board.h"
#include "vector.h"

King::King(Board *board, Coord posn, bool black, int name_value): 
	Piece{board, posn, black, name_value} {
	possible_moves[0] = Coord{1,0};
	possible_moves[1] = Coord{-1,0};
	possible_moves[2] = Coord{0,1};
	possible_moves[3] = Coord{1,1};
	possible_moves[4] = Coord{-1,1};
	possible_moves[5] = Coord{0,-1};
	possible_moves[6] = Coord{1,-1};
	possible_moves[7] = Coord{-1,-1};
	possible_moves[8] = Coord{2,0};
	possible_moves[9] = Coord{-2,0};
}

std::vector<Coord> King::calc_valid_moves(){
	std::vector<Coord> valid;
	//-2 because 8,9 are only valid on first move
	for(int i = 0, i < num_possible_moves-2, i++){
		Coord temp_pos(possible_move[i].x + posn.x, possible_move[i].y + posn.y);
		if(!(temp_pos.x > 7 || temp_pos.x + posn.x < 0 || temp_pos.y + posn.y > 7 || temp_pos.y + posn.y < 0)){
			//check if the move goes into a space an enemy can move to
			board->move_piece(Moving(posn, temp_pos), 0);
			if (is_safe()) valid.push_back(temp_pos));
			board->undo;
		}
	}
	
	if (first_move) {
		//Check if right side is clear
		int i = 1;
		while (posn.x + i < 7) {
			if (board->get_piece(posn.x + i, posn.y)==nullptr) {
				i++;
			} else {
				break;
			}
		}
		if (posn.x + i == 8) {
			Piece *temp = board->get_piece(7, posn.y);
			if (temp != nullptr) {
				//Check if it is a rook (3)
				if (temp->get_name_value == 3) {
					if (temp->isFirstMove()) {
						//3 says it is a castling move
						Coord temp_posn = Coord(posn.x + possible_moves[8].x, posn.y + possible_moves[8].y);
						board->move_piece(Moving(posn, temp_posn), 3);
						if (is_safe()) valid.push_back(temp_posn);
						board->undo;
					}
				}
			}
		}
		
		i = 1;
		while (posn.x - i > 0) {
			if (board->get_piece(posn.x + i, posn.y)==nullptr) {
				i++;
			} else {
				break;
			}
		}
		if (posn.x - i == 0) {
			Piece *temp = board->get_piece(0, posn.y);
			if (temp != nullptr) {
				//Check if it is a rook (3)
				if (temp->get_name_value == 3) {
					if (temp->isFirstMove()) {
						Coord temp_posn = Coord(posn.x + possible_moves[9].x, posn.y + possible_moves[9].y);
						board->move_piece(Moving(posn, temp_posn), 3);
						if (is_safe()) valid.push_back(temp_posn);
						board->undo;
					}
				}
			}
		}
	}
	return valid;
}

void King::first_move_off() {
	first_move = false;
}

void King::first_move_on() {
	first_move = true;
}

bool King::get_first_move() {
	return first_move;
}

