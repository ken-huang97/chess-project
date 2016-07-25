#include <vector>
#include "rook.h"
#include "coord.h"
#include "board.h"

Rook::Rook(Board *board, Coord posn, bool black, int name_value): Piece{board, posn, black, name_value} {
	first_move = true;
}

bool Rook::isFirstMove() {
	return this.first_move;
}

std::vector<Coord> Rook::calculateValidMoves() {
	std::vector<Coord> valid;
	if (is_pinned() == -1) {
		int i = posn.y;
		while (i > 0) {
			i--;
			Piece* temp = board->get_piece(Coord(posn.x, i));
			if (temp == nullptr) {
				valid.push_back(Coord(posn.x, i));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(posn.x, i));
				break;
			}
			else break;
		}
		i = posn.y;
		while (i < 7) {
			i++;
			Piece* temp = board->get_piece(Coord(posn.x, i));
			if (temp == nullptr) {
				valid.push_back(Coord(posn.x, i));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(posn.x, i));
				break;
			}
			else break;
		}	
		i = posn.x;
		while (i > 0) {
			i--;
			Piece* temp = board->get_piece(Coord(i, posn.y));
			if (temp == nullptr) {
			valid.push_back(Coord(i, posn.y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(i, posn.y));
				break;
			}
			else break;
		}
		i = posn.x
		while (i < 7) {
			i++;
			Piece* temp = board->get_piece(Coord(i, posn.y));
			if (temp == nullptr) {
				valid.push_back(Coord(i, posn.y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(i, posn.y));
				break;
			}
			else break;
		}	
	}
	if (is_pinned() == 0) {
		int i = posn.y;
		while (i > 0) {
			i--;
			Piece* temp = board->get_piece(Coord(posn.x, i));
			if (temp == nullptr) {
				valid.push_back(Coord(posn.x, i));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(posn.x, i));
				break;
			}
			else break;
		}
		i = posn.y;
		while (i < 7) {
			i++;
			Piece* temp = board->get_piece(Coord(posn.x, i));
			if (temp == nullptr) {
				valid.push_back(Coord(posn.x, i));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(posn.x, i));
				break;
			}
			else break;
		}
	}
	if (is_pinned() == 2) {
		i = posn.x;
		while (i > 0) {
			i--;
			Piece* temp = board->get_piece(Coord(i, posn.y));
			if (temp == nullptr) {
				valid.push_back(Coord(i, posn.y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(i, posn.y));
				break;
			}
			else break;
		}
		i = posn.x
		while (i < 7) {
			i++;
			Piece* temp = board->get_piece(Coord(i, posn.y));
			if (temp == nullptr) {
				valid.push_back(Coord(i, posn.y));
			}
			else if (temp->is_black() != this.black) {
				valid.push_back(Coord(i, posn.y));
				break;
			}
			else break;
		}
	}
	if (board->get_chk_count() == 0) {
		return valid;
	}
	if (board->get_chk_count() == 1) {
		std::vector<Coord> preventChk;
		std::vector<Coord> newValid;
		Piece* checking_piece = board->get_chk();
		int player = 1;
		if (black) player = 2;
		if (checking_piece->name_value == 1 || checking_piece->name_value == 2) {
			preventChk.push_back(checking_piece->posn);
		}
		if (checking_piece->name_value == 3) {
			if(board->get_chk()->posn.x == board->get_king(player)->posn.x){
				if(board->get_chk()->posn.y > board->get_king(player)->posn.y) {
					for(int i = board->get_king(player)->posn.y + 1; i <= board->get_chk()->posn.y; i++) {
						preventChk.push_back(Coord(board->get_chk()->posn.x, i));
					}
				}
				else {
					for(int i = board->get_king(player)->posn.y - 1; i >= board->get_chk()->posn.y; i--) {
						preventChk.push_back(Coord(board->get_chk()->posn.x, i));
					}
				}
			}
			else{
				if(board->get_chk()->posn.x > board->get_king(player)->posn.x) {
					for(int i = board->get_king(player)->posn.x + 1; i <= board->get_chk()->posn.x; i++) {
						preventChk.push_back(Coord(i, board->get_chk()->posn.y));
					}
				}
				else{
					for(int i = board->get_king(player)->posn.x - 1; i >= board->get_chk()->posn.x; i--) {
						preventChk.push_back(Coord(i, board->get_chk()->posn.y));
					}
				}
			}
		}
		if(board->get_chk()->name_value==4){
			if(board->get_chk()->posn.x > board->get_king(player)->posn.x){
				if(board->get_chk()->posn.y > board->get_king(player)->posn.y){
					for(int i = 1; i<=board->get_chk()->posn.y - board->get_king(player)->posn.y; i++){
						preventChk.push_back(Coord(board->get_king(player)->posn.x+i, board->get_king(player)->posn.y+i));
					}
				}
				else{
					for(int i = 1; i<=board->get_chk()->posn.x - board->get_king(player)->posn.x; i++){
						preventChk.push_back(Coord(board->get_king(player)->posn.x+i, board->get_king(player)->posn.y-i));
					}
				}
			}
			else{
				if(board->get_chk()->posn.y > board->get_king(player)->posn.y){
					for(int i = 1; i<=board->get_chk()->posn.y - board->get_king(player)->posn.y; i++){
						preventChk.push_back(Coord(board->get_king(player)->posn.x-i, board->get_king(player)->posn.y+i));
					}
				}
				else{
					for(int i = 1; i<=board->get_king(player)->posn.x - board->get_chk()->posn.x; i++){
						preventChk.push_back(Coord(board->get_king(player)->posn.x-i, board->get_king(player)->posn.y-i));
					}
				}
			}
		}
		if(board->get_chk()->name_value==5){
			if(board->get_chk()->posn.x == board->get_king(player)->posn.x){
				if(board->get_chk()->posn.y > board->get_king(player)->posn.y) {
					for(int i = board->get_king(player)->posn.y + 1; i <= board->get_chk()->posn.y; i++) {
						preventChk.push_back(Coord(board->get_chk()->posn.x, i));
					}
				}
				else {
					for(int i = board->get_king(player)->posn.y - 1; i >= board->get_chk()->posn.y; i--) {
						preventChk.push_back(Coord(board->get_chk()->posn.x, i));
					}
				}
			}
			else if(board->get_chk()->posn.y == board->get_king(player)->posn.y) {
				if(board->get_chk()->posn.x > board->get_king(player)->posn.x) {
					for(int i = board->get_king(player)->posn.x + 1; i <= board->get_chk()->posn.x; i++) {
						preventChk.push_back(Coord(i, board->get_chk()->posn.y));
					}
				}
				else{
					for(int i = board->get_king(player)->posn.x - 1; i >= board->get_chk()->posn.x; i--) {
						preventChk.push_back(Coord(i, board->get_chk()->posn.y));
					}
				}
			}
			else if(board->get_chk()->posn.x > board->get_king(player)->posn.x) {
				if(board->get_chk()->posn.y > board->get_king(player)->posn.y){
					for(int i = 1; i<=board->get_chk()->posn.y - board->get_king(player)->posn.y; i++){
						preventChk.push_back(Coord(board->get_king(player)->posn.x+i, board->get_king(player)->posn.y+i));
					}
				}
				else{
					for(int i = 1; i<=board->get_chk()->posn.x - board->get_king(player)->posn.x; i++){
						preventChk.push_back(Coord(board->get_king(player)->posn.x+i, board->get_king(player)->posn.y-i));
					}
				}
			}
			else {
				if(board->get_chk()->posn.y > board->get_king(player)->posn.y){
					for(int i = 1; i<=board->get_chk()->posn.y - board->get_king(player)->posn.y; i++){
						preventChk.push_back(Coord(board->get_king(player)->posn.x-i, board->get_king(player)->posn.y+i));
					}
				}
				else{
					for(int i = 1; i<=board->get_king(player)->posn.x - board->get_chk()->posn.x; i++){
						preventChk.push_back(Coord(board->get_king(player)->posn.x-i, board->get_king(player)->posn.y-i));
					}
				}
			}
		}
		return newValid;
	}
}
