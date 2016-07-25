#include "knight.h"
#include "board.h"
#include <vector>

Knight::Knight(Board *board, Coord posn, bool black, bool name_value): Piece{board, posn, is_black, name_value}{
	possible_moves[0]=Coord(-2,1);
	possible_moves[1]=Coord(2,1);
	possible_moves[2]=Coord(-2,-1);
	possible_moves[3]=Coord(2,-1);
	possible_moves[4]=Coord(-1,2);
	possible_moves[5]=Coord(1,2);
	possible_moves[6]=Coord(-1,-2);
	possible_moves[7]=Coord(1,-2);
}

std::vector<Coord> Knight::calc_valid_moves(){
	std::vector<Coord> valid;
	if(is_pinned()==-1){
		for(int i = 0; i<num_possible_moves; i++){
			//Checks to see if on the board
			if(!(possible_move[i].x + posn.x > 7 || possible_move[i].x + posn.x < 0 || possible_move[i].y + posn.y > 7 || possible_move[i].y + posn.y < 0)){
				Piece temp* = board->get_piece(possible_move[i].x + posn.x, possible_move[i].y + posn.y);
				//See if it is moving to an empty space or a space that doesn't contain one
				//of our own pieces
				if(temp==nullptr){
					valid.push_back(Coord(possible_move[i].x + posn.x, possible_move[i].y + posn.y));
				}
				else if(temp->is_black() != this->black){
					valid.push_back(Coord(possible_move[i].x + posn.x, possible_move[i].y + posn.y));
				}
			}
		}
	}
	return valid;
}
