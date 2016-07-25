
void move_piece(Moving mov, int type){
	//Move type 0 is any normal move being, moving to an empty space or capturing an enemy piece
	//Move type 1 is a pawn promotion
	//Move type 2 is a en passant capture move
	//Move type 3 is a castling move

	//Creates an undoInfo struct that keeps track of the current moves info
	undoInfo current_info;

	//the move type is set to be the type that in given
	//and the Moving mov struct is stored
	current_info.type_move = type;
	current_info.mov = mov;

	//
	if(type==0){
		current_info.destroy.push_back(piece_array[mov.end.y][mov.end.x]);
		if(current_info.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_on();
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
		if(current_info.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_on();
		current_info.destroy.push_back(piece_array[mov.start.y][mov.start.x]);
		if(current_info.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_on();
		piece_array[mov.start.y][mov.start.x] = nullptr;
		piece_array[mov.end.y][mov.end.x] = nullptr;
		current_info.first_move_chk=0;
	}
	else if(type==2){
		current_info.destroy.push_back(piece_array[mov.end.y][mov.end.x]);
		if(current_info.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_on();
		if(mov.end.x-mov.start.x > 0){
			current_info.destroy.push_back(piece_array[mov.start.y][mov.start.x+1]);
			if(current_info.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_on();
			piece_array[mov.start.y][mov.start.x+1] = nullptr;
		}
		else{
			current_info.destroy.push_back(piece_array[mov.start.y][mov.start.x-1]);
			if(current_info.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_on();
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
		if(last_move.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_off();
		piece_array[last_move.mov.end.y][last_move.mov.end.x] = last_move.destroy.back();
		last_move.destroy.clear();
	}
	else if(last_move.type_move==1){
		delete piece_array[last_move.mov.end.y][last_move.mov.end.x];
		piece_array[last_move.mov.end.y][last_move.mov.end.x] = nullptr;
		if(last_move.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_off();
		piece_array[last_move.mov.start.y][last_move.mov.start.x]=last_move.destroy.back();
		last_move.destroy.pop_back();
		if(last_move.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_off();
		piece_array[last_move.mov.end.y][last_move.mov.end.x]=last_move.destroy.back();
		last_move.destroy.clear();
	}
	else if(last_move.type_move==2){
		if(last_move.mov.end.x-last_move.mov.start.x > 0){
			if(last_move.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_off();
			piece_array[mov.start.y][mov.start.x+1] = last_move.destroy.back();
		}
		else{
			if(last_move.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_off();
			piece_array[mov.start.y][mov.start.x-1] = last_move.destroy.back();
		}
		last_move.destroy.pop_back();
		piece_array[last_move.mov.start.y][last_move.mov.start.x] = piece_array[last_move.mov.end.y][last_move.mov.end.x];
		piece_array[last_move.mov.start.y][last_move.mov.start.x]->update_posn(last_move.mov.start);
		if(last_move.destroy.back()!=nullptr) current_info.destroy.back()->destroyed_off();
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
	for (std::vector<int>::iterator i = black_pieces.begin(); i != black_pieces.end(); ++i) {
		if (black_pieces[i] != nullptr) delete black_pieces[i];
	}
	for (std::vector<int>::iterator i = white_pieces.begin(); i != white_pieces.end(); ++i) {
		if (white_pieces[i] != nullptr) delete white_pieces[i];
	}
	for (std::vector<int>::iterator i = moves_made.begin(); i != moves_made.end(); ++i) {
		if (moves_made[i] != nullptr) delete moves_made[i];
	}
	for (std::vector<int>::iterator i = destroy.begin(); i != destroy.end(); ++i) {
		if (destroy[i] != nullptr) delete destroy[i];
	}
	for (std::vector<int>::iterator i = possible_moves.begin(); i != possible_moves.end(); ++i) {
		if (possible_moves[i] != nullptr) delete possible_moves[i];
	}
	black_pieces.clear();
	white_pieces.clear();
	moves_made.clear();
	destroy.clear();
	possible_moves.clear();
}

void Board::setBoard() {
	this->reset();
	for (int i = 7; i > -1; i—-) {
		piece_array[7][4] = new Piece(this, Coord(0,4), 0, 6);
		white_pieces.push_back(piece_array[7][4]);
		if (i == 7) {
			for (int j = 0; j < 8; j++) {
				if (j == 0 || j == 7) piece_array[i][j] = new Piece(this, Coord(i,j), 0, 3);
				if (j == 1 || j == 6) piece_array[i][j] = new Piece(this, Coord(i,j), 0, 2);
				if (j == 2 || j == 5) piece_array[i][j] = new Piece(this, Coord(i,j), 0, 4);
				if (j == 3) piece_array[i][j] = new Piece(this, Coord(i,j), 0, 5);
			}
			white_pieces.push_back(piece_array[i][3]);
			white_pieces.push_back(piece_array[i][2]);
			white_pieces.push_back(piece_array[i][5]);
			white_pieces.push_back(piece_array[i][0]);
			white_pieces.push_back(piece_array[i][7]);
			white_pieces.push_back(piece_array[i][1]);
			white_pieces.push_back(piece_array[i][6]);
		}
		if (i == 6) {
			for (int j = 0; j < 8; j++) {
				piece_array[i][j] = new Piece(this, Coord(i,j), 0, 1);
				white_pieces.push_back(piece_array[i][j]);
			}
		}
		piece_array[7][4] = new Piece(this, Coord(7,4), 1, 6);
		black_pieces.push_back(piece_array[7][4]);
		if (i == 1) {
			for (int j = 0; j < 8; j++) {
				piece_array[i][j] = new Piece(this, Coord(i,j), 1, 1);
				black_pieces.push_back(piece_array[i][j]);
			}
		}
		if (i == 0) {
			for (int j = 0; j < 8; j++) {
				if (j == 0 || j == 7) piece_array[i][j] = new Piece(this, Coord(i,j), 1, 3);
				if (j == 1 || j == 6) piece_array[i][j] = new Piece(this, Coord(i,j), 1, 2);
				if (j == 2 || j == 5) piece_array[i][j] = new Piece(this, Coord(i,j), 1, 4);
				if (j == 3) piece_array[i][j] = new Piece(this, Coord(i,j), 1, 5);
			}
			black_pieces.push_back(piece_array[i][3]);
			black_pieces.push_back(piece_array[i][2]);
			black_pieces.push_back(piece_array[i][5]);
			black_pieces.push_back(piece_array[i][0]);
			black_pieces.push_back(piece_array[i][7]);
			black_pieces.push_back(piece_array[i][1]);
			black_pieces.push_back(piece_array[i][6]);

		}
	}
	calc_all_valid_moves(1);
}



void Board::calc_all_valid_moves(int player) {
	this.possible_moves.clear();
	std::vector<Piece *> all_pieces = board->get_player_pieces(player);
	for (int i = 0; i < all_pieces.size(); i++) {
		std::vector<Moving> temp = all_pieces[i]->calc_valid_moves();
		//into vector of all moves
		possible_moves.insert(std::possible_moves.end(), std::temp.start(), std::temp.end());
	}
}

//Return -1 for not over, 0 for stalemate, 1 for white, 2 for black
int Board::end_of_game_check(int enemy) {
	if (possible_moves.empty()) {
		if(get_king(enemy)->is_safe()) {
			std::cout << "Stalemate!" << std::cout;
			return 0;
		} else if (player_black){
			std::cout << "Checkmate! Black wins!" << std::cout;
			return 2;
		} else {
			std::cout << "Checkmate! White wins!" << std::cout;
			return 1;
		}
	} else {
		return -1;
	}
}

//Cpu move
int Board::call_move(int player) {
	bool player_black = (player == 2) ? true : false;
	int enemy = (player_black) ? 1 : 2;
	if (player_black) {
		controller1->move();
	} else {
		controller2->move();
	}
	calc_all_valid_moves(enemy);
	//Cpu move can never fail.
	//If there were no possible moves, it would not be called
	draw();
	return end_of_game_check(enemy);
}

//Return end_of_game_check(enemy) if succesful, else -2 
//Human move
int Board::call_move(Moving move, int player) {
	bool successful_move = false;
	bool player_black = (player == 2) ? true : false;
	int enemy = (player_black) ? 1 : 2;
	if (get_piece(move.start)->is_black() != player_black) {
		std::cout << "Invalid move" << std::endl;
	}
	//Human move can fail if they input a bad input
	successful_move = (player_black) ? controller2->move(move) : controller1->move(move);
	if (successful_move) {
		calc_all_valid_moves(enemy);
		draw();
		return end_of_game_check(enemy);
	}
	return -2;
}

//Return end_of_game_check() if succesful, else -2 
//Human move with promote
int Board::call_move(Moving move, int name_value, int player) {
	bool player_black = (player == 2) ? true : false;
	int enemy = (player_black) ? 1 : 2;
	if (get_piece(move.start)->is_black() != player_black) {
		std::cout << "Invalid move" << std::endl;
	}
	successful_move = (player_black) ? controller2->move(move, name_value) : controller1->move(move, name_value);
	if (successful_move) {
		calc_all_valid_moves(enemy);
		draw();
		return end_of_game_check(enemy);
	}
	return -2;
}

void Board::add_players(int p1, int p2) {
	//0 for human
	if (p1 == 0) controller1 = new Human(this, 1);
	else controller1 = new Computer(this, 1, p1);
	
	if (p2 == 0) controller1 = new Human(this, 1);
	else controller1 = new Computer(this, 1, p2);
}

Board::Board() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			piece_array[i][j] = nullptr;
		}
	}
	controller1 = nullptr;
	controller2 = nullptr;
}

bool Computer::isCheckingMove(const Moving &move) {
	int pieceType = board->get_piece(move.start)->get_name_value();
	bool isBlack = board->get_piece(move.start)->is_black();
	int moveType;
	if (pieceType == 1 && move.start.x - move.end.x != 0 && board->get_piece(move.end) == nullptr) {
		moveType = 2;
	} else if (pieceType == 1) {
		if (move->end.y == 0 || move->end.y == 7) {
			moveType = 1;
		}
	} else if (pieceType == 6 && abs(move.start.x - move.end.x) == 2)
		moveType = 3;
	} else {
		moveType = 0;
	}
	board->move_piece(move, moveType);
	int otherplayer;
	if (isBlack) {
		otherplayer = 1;
	} else {
		otherplayer = 2;
	}
	if (board->get_king(otherplayer).is_safe()) {
		board->undo();
		return false;
	} else {
		board->undo();
		return true;
	}
}
