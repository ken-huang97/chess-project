Computer::Computer(Board *board, int player, int level): Controller{board, player}, level{level} {}


bool Computer::is_capture_move(const Moving &move) {
	//Special case for en_passant captures
	if (board->get_piece(move.start)->get_name_value()==1){
		//if it moved diagonally but there was no piece at the end
		// then it must be en_passant
		if (move.end.x != move.begin.x && board->get_piece(move.end) == nullptr {
			return true;
	}
	
	//Normal case, check if end position is occupied (if it is, it is an enemy because we are given a valid move)
	Piece *temp = board->get_piece(move.end);
	if (temp != nullptr) {
		return true;
	} else {
		return false;
	}
}

bool Computer::isCheckingMove(const Moving &move) {
	int pieceType = board->get_piece(move.start)->get_name_value();
	bool isBlack = board->get_piece(move.start)->is_black();
	int moveType;
	if (pieceType == 1 && move.start.x != move.end.x && board->get_piece(move.end) == nullptr) {
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

bool Computer::is_safe_move(const Moving &move) {
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
	
	if(board->get_piece(move.end).is_safe()) {
		board->undo();
		return true;
	} else {
		board->undo();
		return false;
	}
}

void Computer::move() override{
	std::vector<vector<Moving>> move_priority;
	std::vector<Piece *> all_pieces = board->get_player_pieces(player);
	std::vector<Moving> all_moves = board->get_valid_moves();
	
	move_priority.push_back(all_moves);
	
	if (level >= 2) {
		vector<Moving> checks_or_captures;
		vector<Moving> checks_and_captures;
		
		for (int i = 0; i < all_moves.size(); i++) {
			if (isCheckingMove(all_moves[i])) {
				if (is_capture_move(all_moves[i]) {
					checks_and_captures.push_back(all_moves[i]);
				} else {
					checks_or_captures.push_back(all_moves[i]);
				}
			} else if (is_capture_move(all_moves[i])) {
				checks_or_captures.push_back(all_moves[i]);
			}
		}

		
		move_priority.push_back(checks_or_captures);
		move_priority.push_back(checks_and_captures);
	} 
	
	if (level >= 3) {
		vector<Moving> safe;
		vector<Moving> safe_and_ch_or_ca;
		vector<Moving> safe_and_ch_and_ca;
		
		//take from all moves
		for (int i = 0; i < move_priority[0].size(); i++) {
			Moving temp = move_priority[0][i];
			if (is_safe_move(temp)) {
				safe.push_back(temp);
			}
		}
		for (int i = 0; i < move_priority[1].size(); i++) {
			Moving temp = move_priority[1][i];
			if (is_safe_move(temp)) {
				safe_and_ch_or_ca.push_back(temp);
			}
		}
		for (int i = 0; i < move_priority[2].size(); i++) {
			Moving temp = move_priority[2][i];
			if (is_safe_move(temp)) {
				safe_and_ch_and_ca.push_back(temp);
			}
		}
		move_priority.push_back(safe);
		move_priority.push_back(safe_and_ch_or_ca);
		move_priority.push_back(safe_and_ch_and_ca);
	}
	if (level >= 4) {
		/* black magic */
	}
	
	//Choose the highest priority, and choose a random move from it
	for (auto prio_level = move_priority.rbegin(); prio_level != my_vector.rend(); ++prio_level) {
		if (!prio_level->empty()) {
			board->update(*prio_level[rand() % prio_level.size()]);
			break;
		}
	}
}
