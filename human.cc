#include "human.h"

//Constructor
Human::Human(int player): Controller{player} {}

bool Human::move(Moving inputMove){
	//isValid tracks to see if user input is valid
	bool isValid = false;
	//valid is a vector of all valid moves for player
	vector<Moving> valid = board->get_valid_moves(player);

	for(int i=0; i<valid.size(); i++){
		//Checks to see if user inputted move is in the vector of all valid moves
		if(inputMove==valid[i]){
			//Checks if the move was an en passant move
			if(board->get_piece(inputMove.start)->get_name_value()==1){
				if(board->get_piece(inputMove.start)->get_is_en_passant()[i]){
					board->move_piece(inputMove, 2);
				}
				else board->move_piece(inputMove, 0);
			}
			//Checks if the move was a castling move
			else if(board->get_piece(inputMove.start)->get_name_value()==6){
				if(board->get_piece(inputMove.start)->get_castle()[i]){
					board->move_piece(inputMove, 3);
				}
				else board->move_piece(inputMove, 0);
			}
			//Else just a normal move
			else board->move_piece(inputMove, 0);
			//Checks to see if move is done is the king safe
			//if yes it is a valid move
			if(board->get_king(player).is_safe()){
				isValid = true;
				break;
			}
			//else undo the move and it is not a valid move
			board->undo();
			break;
		}
	}
	return isValid;
}

bool Human::move(Moving inputMove, int name){
	//Similar to above except this move is overrided for promoting a pawn
	bool isValid = false;
	vector<Moving> valid = board->get_valid_moves(player);
	for(int i=0; i<valid.size(); i++){
		//Checks if it is a pawn that is moved, if it is approaching the right end of the board
		//Player 1 is white, player 2 is black
		if(inputMove==valid[i] && board->get_piece(inputMove.start)->get_name_value()==1 && player-1*7==inputMove.end.y){
			board->move_piece(inputMove, 1);
			board->get_piece(inputMove.start)->promote(name, inputMove.end);
		}
		if(board->get_king(player).is_safe()){
				isValid = true;
				break;
			}
		board->undo();
		break;
	}
	return isValid;
}
