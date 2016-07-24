#include "human.h"

Human::Human(int player): Controller{player} {}

void Human::move(Moving inputMove){
	vector<Moving> valid = board->get_valid_moves(player);
	for(int i=0; i<valid.size(); i++){
		if(inputMove==valid[i]){
			board->move_piece(inputMove);
			break;
		}
	}
}

void Human::move(Moving inputMove, int name){
	vector<Moving> valid = board->get_valid_moves(player);
	for(int i=0; i<valid.size(); i++){
		if(inputMove==valid[i] && board->get_piece(inputMove.start)->get_name_value()==1 && player-1*7==inputMove.end.y){
			board->promote_move_piece(inputMove);
			board->get_piece(inputMove.start)->promote(name, inputMove.end);
			break;
		}
	}
}
