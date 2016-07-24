#include <vector>
#include "pawn.h"
#include "board.h"

Pawn::Pawn(Board *board, Coord posn, bool black, int name_value): Piece{board, posn, black, name_value} {
	bool en_passant = false;
	bool first_move = true;

	possible_move[0]=Coord(0,1);
	possible_move[1]=Coord(1,1);
	possible_move[2]=Coord(-1,1);
	possible_move[3]=Coord(0,2);
}

void Pawn::Promote(int name, Coord position){
	board->place_piece(name, position, black);
}
void Pawn::en_passant_off(){
	en_passant=false;
}
void Pawn::en_passant_on(){
	en_passant=true;
}
bool Pawn::get_en_passant(){
	return en_passant;
}
void Pawn::first_move_off(){
	first_move=false;
}
void Pawn::first_move_on(){
	first_move=true;
}
bool Pawn::get_first_move(){
	return first_move;
}

//Returns a vector of valid place to move to
std::vector<Coord> Pawn::calc_valid_moves(){
	//valid is a vector that contains valid place to move to if king is not checked
	std::vector<Coord> valid;
	//Makes sure move result doesn't go off the board
	if(!(possible_move[i].x + posn.x > 7 || possible_move[i].x + posn.x < 0 || possible_move[i].y + posn.y > 7 || possible_move[i].y + posn.y < 0)){
		//Check to see if the pawn can move forward
		//The is_pinned is for making sure that the pawn moving won't cause the king to be checked
		if(board->get_piece(Coord(possible_move[0].x + posn.x, possible_move[0].y + posn.y))==nullptr && (is_pinned()==-1 || is_pinned()==0)){
			valid.push_back(Coord(possible_move[i].x + posn.x, possible_move[i].y + posn.y));
			is_en_passant.push_back(false);
		}
		//Check to see if the pawn can move sideways to capture a piece
		else if(board->get_piece(Coord(possible_move[1].x + posn.x, possible_move[1].y + posn.y))!=nullptr){
			if(board->get_piece(Coord(possible_move[1].x + posn.x, possible_move[1].y + posn.y))->is_black() != this->black && (is_pinned()==-1 || is_pinned()==1)){
				valid.push_back(Coord(possible_move[1].x + posn.x, possible_move[1].y + posn.y));
			}
		}
		else if(board->get_piece(Coord(possible_move[2].x + posn.x, possible_move[2].y + posn.y))!=nullptr){
			if(board->get_piece(Coord(possible_move[2].x + posn.x, possible_move[2].y + posn.y))->is_black() != this->black && (is_pinned()==-1 || is_pinned()==3)){
				valid.push_back(Coord(possible_move[2].x + posn.x, possible_move[2].y + posn.y));
				is_en_passant.push_back(false);
			}
		}
		else if(board->get_piece(Coord(posn.x+1, posn.y))->get_name_value()==1){
			if(board->get_piece(Coord(posn.x+1, posn.y))->get_en_passant()){
				valid.push_back(Coord(possible_move[1].x + posn.x, possible_move[1].y + posn.y));
				is_en_passant.push_back(true);
			}
		}
		else if(board->get_piece(Coord(posn.x-1, posn.y))->get_name_value()==1){
			if(board->get_piece(Coord(posn.x-1, posn.y))->get_en_passant()){
				valid.push_back(Coord(possible_move[-1].x + posn.x, possible_move[1].y + posn.y));
				is_en_passant.push_back(true);
			}
		}
		//If it is the pawns first move
		else if(first_move == true && board->get_piece(Coord(posn.x, 1 + posn.y))==nullptr 
			&& board->get_piece(Coord(posn.x, 2 + posn.y))==nullptr  
			&& (is_pinned()==-1 || is_pinned()==0)){
			valid.push_back(Coord(possible_move[3].x + posn.x, possible_move[3].y + posn.y));
			is_en_passant.push_back(false);
		}
	}
}

std::vector<bool> Pawn::get_is_en_passant(){
	return is_en_passant;
}
