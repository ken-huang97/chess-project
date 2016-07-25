#include "human.h"

Human::Human(int player): Controller{player} {}

void Human::move(Moving inputMove){
	vector<Moving> valid = board->get_valid_moves(player);
	for(int i=0; i<valid.size(); i++){
		if(inputMove==valid[i]){
			if(board->get_piece(inputMove.start)->get_name_value()==1){
				if(board->get_piece(inputMove.start)->get_is_en_passant()[i]){
					board->move_piece(inputMove, 2);
				}
				else board->move_piece(inputMove, 0);
			}

			else if(board->get_piece(inputMove.start)->get_name_value()==6){
				if(board->get_piece(inputMove.start)->get_castle()[i]){
					board->move_piece(inputMove, 3);
				}
				else board->move_piece(inputMove, 0);
			}

			else board->move_piece(inputMove, 0);

			if(board->get_king(player).is_safe()){
				break;
			}
			board->undo();
		}
	}
}

void Human::move(Moving inputMove, int name){
	vector<Moving> valid = board->get_valid_moves(player);
	for(int i=0; i<valid.size(); i++){
		if(inputMove==valid[i] && board->get_piece(inputMove.start)->get_name_value()==1 && player-1*7==inputMove.end.y){
			board->move_piece(inputMove, 1);
			board->get_piece(inputMove.start)->promote(name, inputMove.end);
		}
		if(board->get_king(player).is_safe()){
				break;
			}
		board->undo();
	}
}
