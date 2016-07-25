vector<undoInfo> move_list;
void move_piece(Moving mov, int type){
	undoInfo current_info;
	current_info.type_move = type;
	current_info.mov = mov;
	if(type==0){
		current_info.destroy.push_back(piece_array[mov.end.y][mov.end.x]);
		piece_array[mov.end.y][move.end.x] = piece_array[mov.start.y][mov.start.x];
		piece_array[mov.start.y][mov.start.x] = nullptr;
		piece_array[mov.end.y][mov.end.x]->update_posn(mov.end);
		int nameVal = piece_array[mov.end.y][mov.end.x]->get_name_value();
		if(nameVal==1 || nameVal==3 || nameVal==6){
			if(piece_array[mov.end.y][mov.end.x]->get_first_move()){
				piece_array[mov.end.y][mov.end.x]->first_move_off();
				current_info.first_move_chk=1;
			}
			else current_info.first_move_chk=0;
		}
		else current_info.first_move_chk=0;
	}
	else if(type==1){
		current_info.destroy.push_back(piece_array[mov.end.y][mov.end.x]);
		current_info.destroy.push_back(piece_array[mov.start.y][mov.start.x]);
		piece_array[mov.start.y][mov.start.x] = nullptr;
		piece_array[mov.end.y][mov.end.x] = nullptr;
		current_info.first_move_chk=0;
	}
	else if(type==2){
		current_info.destroy.push_back(piece_array[mov.end.y][mov.end.x]);
		if(mov.end.x-move.star.x > 0){
			current_info.destroy.push_back(piece_array[mov.start.y][mov.start.x+1]);
			piece_array[mov.start.y][mov.start.x+1] = nullptr;
		}
		else{
			current_info.destroy.push_back(piece_array[mov.start.y][mov.start.x-1]);
			piece_array[mov.start.y][mov.start.x-1] = nullptr;
		}
		piece_array[mov.end.y][move.end.x] = piece_array[mov.start.y][mov.start.x];
		piece_array[mov.start.y][mov.start.x] = nullptr;
		piece_array[mov.end.y][mov.end.x]->update_posn(mov.end);
		current_info.first_move_chk=0;
	}
	else if(type==3){
		if(mov.start.x-mov.end.x>0){
			piece_array[mov.end.y][move.end.x] = piece_array[mov.start.y][mov.start.x];
			piece_array[mov.end.y][3] = piece_array[mov.start.y][0];
			piece_array[mov.start.y][mov.start.x] = nullptr;
			piece_array[mov.start.y][0] = nullptr;
		}
		else{
			piece_array[mov.end.y][move.end.x] = piece_array[mov.start.y][mov.start.x];
			piece_array[mov.end.y][5] = piece_array[mov.start.y][7];
			piece_array[mov.start.y][mov.start.x] = nullptr;
			piece_array[mov.start.y][7] = nullptr;
		}
	}
}

/**void undo(){
	if(destroy.size()>moves_made.size()){
		delete piece_array[moves_made.back().end.y][moves_made.back().end.x];
		destroy.pop_back();
	}
	piece_array[moves_made.back().start.y][moves_made.back().start.x] = piece_array[moves_made.back().end.y][moves_made.back().end.x];
	piece_array[moves_made.back().start.y][moves_made.back().start.x]->update_posn(moves_made.back().start);
	if(first_move_chk.back()==1){
		piece_array[moves_made.back().start.y][moves_made.back().start.x]->first_move_on();
	}
	piece_array[moves_made.back().end.y][moves_made.back().end.x] = destroy.back();
	first_move_chk.pop_back();
	moves_made.pop_back();
	destroy.pop_back();
}**/

Piece* get_piece(Coord posn){
	return piece_array[posn.y][posn.x];
}
Piece* get_king(int player){
	if(player==1) return white_pieces[0];
	else return black_pieces[0];
}

vector<Piece*> get_player_pieces(int player){
	if(player==1) return white_pieces;
	else return black_pieces;
}


