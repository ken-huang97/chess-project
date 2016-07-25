#ifndef __BOARD_H__
#define __BOARD_H__
#include <array>
#include "piece.h"

struct Coord;
struct Piece;
struct Moving;

class Board {
		Piece* piece_array[][];
		std::vector<Piece*> black_pieces;
		std::vector<Piece*> white_pieces;
		std::vector<Moving> moves_made;
		std::vector<Piece*> destroy;
		std::vector<Moving> possible_moves;
	public:
		Board();
		~Board();
		void setBoard();
		void place_piece();
		void reset();
		void draw();
		void calc_all_valid_moves(int player);
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
}

void Board::setBoard() {
	this->reset();
	for (int i = 0; i < 8; i++) {
		piece_array[0][4] = new Piece(this, Coord(0,4), 0, 6);
		white_pieces.push_back(piece_array[0][4]);
		if (i == 0) {
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
		if (i == 1) {
			for (int j = 0; j < 8; j++) {
				piece_array[i][j] = new Piece(this, Coord(i,j), 0, 1);
				white_pieces.push_back(piece_array[i][j]);
			}
		}
		piece_array[7][4] = new Piece(this, Coord(7,4), 1, 6);
		black_pieces.push_back(piece_array[7][4]);
		if (i == 6) {
			for (int j = 0; j < 8; j++) {
				piece_array[i][j] = new Piece(this, Coord(i,j), 1, 1);
				black_pieces.push_back(piece_array[i][j]);
			}
		}
		if (i == 7) {
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

void Board::place_piece(int name, Coord posn, Bool black) {
	if (posn.x > 7 || posn.x < 0 || posn.y > 7 || posn.y < 0 || name > 6 || name < 1) {
		std::cout << "Invalid placement" << std::endl;
		return;
	}
	if (this->piece_array[posn.y][posn.x] != nullptr) {
		if (this->piece_array[posn.y][posn.x]->is_black()) {
			for (std::vector<int>::iterator i = black_pieces.begin(); i != black_pieces.end(); i++) {
				if (black_pieces[i]->posn.x == posn.x && black_pieces[i]->posn.y == posn.y) {
					black_pieces.erase(i);
					this->piece_array[posn.y][posn.x] = nullptr;
					break;
				}
			}
		}
		else {
			for (std::vector<int>::iterator i = white_pieces.begin(); i < white_pieces.end(); i++) {
				if (white_pieces[i]->posn.x == posn.x && white_pieces[i]->posn.y == posn.y) {
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
