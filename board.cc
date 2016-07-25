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
				if(nameVal==1 && abs(mov.end.y-mov.start.y)){
					piece_array[mov.end.y][mov.end.x]->en_passant_on();
				}
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
		if(mov.end.x-mov.start.x > 0){
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
		current_info.first_move_chk=1;
		if(mov.start.x>mov.end.x){
			piece_array[mov.end.y][move.end.x] = piece_array[mov.start.y][mov.start.x];
			piece_array[mov.end.y][3] = piece_array[mov.start.y][0];
			piece_array[mov.end.y][move.end.x]->update_posn(move.end);
			piece_array[mov.end.y][3]->update_posn(Coord(mov.end.y,3));
			piece_array[mov.end.y][mov.end.x]->first_move_off();
			piece_array[mov.end.y][3]->first_move_off();
			piece_array[mov.start.y][mov.start.x] = nullptr;
			piece_array[mov.start.y][0] = nullptr;
		}
		else{
			piece_array[mov.end.y][move.end.x] = piece_array[mov.start.y][mov.start.x];
			piece_array[mov.end.y][5] = piece_array[mov.start.y][7];
			piece_array[mov.end.y][move.end.x]->update_posn(move.end);
			piece_array[mov.end.y][5]->update_posn(Coord(mov.end.y,5));
			piece_array[mov.end.y][mov.end.x]->first_move_off();
			piece_array[mov.end.y][5]->first_move_off();
			piece_array[mov.start.y][mov.start.x] = nullptr;
			piece_array[mov.start.y][7] = nullptr;
		}
	}
}

void undo(){
	undoInfo last_move = move_list.back();

	if(last_move.type_move==0){
		piece_array[last_move.mov.start.y][last_move.mov.start.x] = piece_array[last_move.mov.end.y][last_move.mov.end.x];
		piece_array[last_move.mov.start.y][last_move.mov.start.x]->update_posn(last_move.mov.start);
		if(last_move.first_move_chk==1){
			piece_array[last_move.mov.start.y][last_move.mov.start.x]->first_move_on();
			if(piece_array[last_move.mov.start.y][last_move.mov.start.x]->get_name_value()==1 && abs(last_move.mov.end.y-last_move.mov.start.y)){
				piece_array[last_move.mov.start.y][last_move.mov.start.x]->en_passant_off();
			}
		}
		piece_array[last_move.mov.end.y][last_move.mov.end.x] = last_move.destroy.back();
		last_move.destroy.clear();
	}
	else if(last_move.type_move==1){
		delete piece_array[last_move.mov.end.y][last_move.mov.end.x];
		piece_array[last_move.mov.end.y][last_move.mov.end.x] = nullptr;
		piece_array[last_move.mov.start.y][last_move.mov.start.x]=last_move.destroy.back();
		last_move.destroy.pop_back();
		piece_array[last_move.mov.end.y][last_move.mov.end.x]=last_move.destroy.back();
		last_move.destroy.clear();
	}
	else if(last_move.type_move==2){
		if(last_move.mov.end.x-last_move.mov.start.x > 0){
			piece_array[mov.start.y][mov.start.x+1] = last_move.destroy.back();
		}
		else{
			piece_array[mov.start.y][mov.start.x-1] = last_move.destroy.back();
		}
		last_move.destroy.pop_back();
		piece_array[last_move.mov.start.y][last_move.mov.start.x] = piece_array[last_move.mov.end.y][last_move.mov.end.x];
		piece_array[last_move.mov.start.y][last_move.mov.start.x]->update_posn(last_move.mov.start);
		piece_array[last_move.mov.end.y][last_move.mov.end.x] = last_move.destroy.back();
		last_move.destroy.clear();
	}
	else if(last_move.type_move==3){
		if(last_move.mov.start.x-last_move.mov.end.x>0){
			piece_array[last_move.mov.start.y][last_move.move.start.x] = piece_array[last_move.mov.end.y][last_move.mov.end.x];
			piece_array[last_move.mov.end.y][0] = piece_array[last_move.mov.start.y][3];
			piece_array[last_move.mov.start.y][last_move.move.start.x]->update_posn(last_move.mov.start);
			piece_array[last_move.mov.end.y][0]->update_posn(Coord(last_move.mov.end.y,0));
			piece_array[last_move.mov.start.y][last_move.move.start.x]->first_move_on();
			piece_array[last_move.mov.end.y][0]->first_move_on();
			piece_array[last_move.mov.end.y][last_move.mov.end.x] = nullptr;
			piece_array[last_move.mov.start.y][3] = nullptr;
		}
		else{
			piece_array[last_move.mov.start.y][last_move.move.start.x] = piece_array[last_move.mov.end.y][last_move.mov.end.x];
			piece_array[last_move.mov.end.y][7] = piece_array[last_move.mov.start.y][5];
			piece_array[last_move.mov.start.y][last_move.move.start.x]->update_posn(last_move.mov.start);
			piece_array[last_move.mov.end.y][7]->update_posn(Coord(last_move.mov.end.y,7));
			piece_array[last_move.mov.start.y][last_move.move.start.x]->first_move_on();
			piece_array[last_move.mov.end.y][7]->first_move_on();
			piece_array[last_move.mov.end.y][last_move.mov.end.x] = nullptr;
			piece_array[last_move.mov.start.y][5] = nullptr;
		}
	}
	move_list.pop_back();
}

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

void remove_piece(Coord posn){
	if(piece_array[posn.y][posn.x]->is_black){
		for(int i=0; i<black_pieces.size(); i++){
			if(black_pieces[i].get_posn()==posn){
				black_pieces[i]=nullptr;
			}
		}
	}
	else{
		for(int i=0; i<white_pieces.size(); i++){
			if(white_pieces[i].get_posn()==posn){
				white_pieces[i]=nullptr;
			}
		}
	}
	delete piece_array[posn.y][posn.x];
	piece_array[posn.y][posn.x] = nullptr;
}

void Board::draw() {
	char c;
	int piece_val;
	for (int i = 7; i >= 0; i--) {
		for (int j = 0; j < 8; j++) {
			Piece* curr = this->get_piece(Coord(j,i));
			if (curr == nullptr) {
				if (i % 2 == 1) {
					if (j % 2 == 0) {
						c = ' ';
					} else {
						c = '-';
					}
				} else {
					if (j % 2 == 0) {
						c = '-';
					} else {
						c = ' ';
					}
				}
			} else {
				piece_type = this->get_piece(i,j)->get_name_val();
				if (this->get_piece(i,j)->is_black()) {
					if (piece_type == 1) {
						c = 'p';
					} else if (piece_type == 2) {
						c = 'n';
					} else if (piece_type == 3) {
						c = 'r';
					} else if (piece_type == 4) {
						c = 'b';
					} else if (piece_type == 5) {
						c = 'q';
					} else if (piece_type == 6) {
						c = 'k';
					}
				} else {
					if (piece_type == 1) {
						c = 'P';
					} else if (piece_type == 2) {
						c = 'N';
					} else if (piece_type == 3) {
						c = 'R';
					} else if (piece_type == 4) {
						c = 'B';
					} else if (piece_type == 5) {
						c = 'Q';
					} else if (piece_type == 6) {
						c = 'K';
					}
				}
			}
			std::cout << c;
		}
		std::cout << std::endl;
	}
}

void Board::place_piece(int name, Coord posn, Bool black) {
	if (posn.x > 7 || posn.x < 0 || posn.y > 7 || posn.y < 0 || name > 6 || name < 1) {
		std::cout << "Invalid placement" << std::endl;
		return;
	}
	if (this->piece_array[posn.y][posn.x] != nullptr) {
		if (this->piece_array[posn.y][posn.x]->is_black()) {
			for (std::vector<int>::iterator i = black_pieces.begin(); i != black_pieces.end(); i++) {
				if (black_pieces[i]->get_posn() == posn) {
					black_pieces.erase(i);
					this->piece_array[posn.y][posn.x] = nullptr;
					break;
				}
			}
		}
		else {
			for (std::vector<int>::iterator i = white_pieces.begin(); i != white_pieces.end(); i++) {
				if (white_pieces[i]->get_posn() == posn) {
					white_pieces.erase(i);
					this->piece_array[posn.y][posn.x] = nullptr;
					break;
				}
			}
		}
	}
	piece_array[posn.y][posn.x] = new Piece(this, Coord(posn.x, posn.y), black, name);
	if (this.black) {
		black_pieces.push_back(piece_array[posn.y][posn.x]);
	} else {
		white_pieces.push_back(piece_array[posn.y][posn.x]);
	}
}

void Board::reset() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (piece_array[i][j] != nullptr) {
				piece_array[i][j] = nullptr;
			}
		}
	}
	black_pieces.clear();
	white_pieces.clear();
	moves_made.clear();
	destroy.clear();
	possible_moves.clear();
}
