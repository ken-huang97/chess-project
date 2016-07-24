#include "coord.h"
#include "moving.h"
#include "board.h"
#include "vector.h"

King::King(Coord posn, bool is_black, int name_value): 
	Piece{posn, is_black, name_value} {
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
	std::vector<Moving> compare_valid = (black) ? get_valid_moves(1) : get_valid_moves(0);
	//-2 because 8,9 are only valid on first move
	for(int i = 0, i < num_possible_moves-2, i++){
		Coord temp_pos(possible_move[i].x + posn.x, possible_move[i].x + posn.x);
		if(!(temp_pos.x > 7 || temp_pos.x + posn.x < 0 || temp_pos.y + posn.y > 7 || temp_pos.y + posn.y < 0)){
			//check if the move goes into a space an enemy can move to
			int i = 0;
			while (i < compare_valid.size()) {
				if (compare_valid[i]==temp_pos) break;
				i++;
			}
			if (i == compare_valid.size()){
				Piece temp* = board->get_piece(temp_pos.x, temp_pos.y);
				//If there is no piece there
				if (temp == nullptr) {
					valid.push_back(temp_pos));
				} else if (temp->is_black() != this.black) valid.push_back(temp_pos);
			}
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
						valid.push_back(Coord(possible_move[8].x + posn.x, possible_move[8].y + posn.y));
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
						valid.push_back(Coord(possible_move[9].x + posn.x, possible_move[9].y + posn.y));
					}
				}
			}
		}
	}
	return valid;
}