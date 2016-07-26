#include <sstream>
#include <iostream>
#include <string>

#include "board.h"
#include "coord.h"

//chess must be like a1
Coord chess_to_coord (std::string chess) {
	int x = chess[0] - 'a';
	int y = chess[1] - '1';
	return Coord(x,y);
}

bool proper_chess_move (const std::string chess) {
	if (chess.length() != 2) return false;
	char lower_case = tolower(chess[0]);
	int number = chess[1] - '0';
	if (lower_case >= 'a' && lower_case <= 'h') {
		if (number >= 1 && number <= 8) {
			return true;
		}
	}
	return false;
}

int main() {
	float white_wins = 0;
	float black_wins = 0;
	bool black_turn = false;
	bool game_running = false;
	Board board;
	while (true){
		std::string input_string;
		getline(std::cin, input_string);
		istringstream ss{input_string};
		if (std::cin) {
			std::string first_command;
			ss >> first_command;
			
			if (first_command == "game") {
				if (game_running) {
					std::cout << "Finish this game first!" << std::endl;
				} else {
					std::string player1_type;
					std::string player2_type;
					
					int add_type1 = -1;
					int add_type2 = -1;
					if (ss >> player1_type) {
						if (ss >> player2_type) {
							if (player1_type == "human") {
								add_type1 = 0;
							} else {
								int level_check1 = player1_type.back() - '0';
								player1_type.pop_back();
								if (player1_type == "computer") {
									if (level_check1 > 0 && level_check1 <= 4) {
										add_type1 = level_check1;
									} else {
										std::cout << "Invalid computer level" << std::endl;
									}
								} else {
									std::cout << "Invalid controller" << std::endl;
								}
							}
							
							if (add_type1 >= 0) {
								if (player2_type == "human") {
									add_type2 = 0;
								} else {
									int level_check2 = player2_type.back() - '0';
									player2_type.pop_back();
									if (player2_type == "computer") {
										if (level_check2 > 0 && level_check2 <= 4) {
											add_type2 = level_check2;
										} else {
											std::cout << "Invalid computer level" << std::endl;
										}
									} else {
										std::cout << "Invalid controller" << std::endl;
									}
								}
							}
							
							if (add_type1 >= 0 && add_type2 >= 0) {
								board.add_players(add_type1, add_type2);
							}

						} else {
							std::cout << "Enter two controllers" << std::endl;
						}
					} else {
						std::cout << "Enter two controllers" << std::endl;
					}
				}
			} else if (first_command == "resign") {
				if (black_turn) {
					white_wins++;
					std::cout <<  "White wins!" << std::endl;
					board.reset();
					game_running = false;
				} else {
					black_wins++;
					std::cout <<  "Black wins!" << std::endl;
					board.reset();
					game_running = false;
				}
			} else if (first_command == "move") {
				std::string start_string;
				std::string end_string;
				char pawn_promote;
				int promote_name_value = -1;
				int player_to_move = (black_turn) ? 2 : 1;
				int game_state = -3;
				if (ss >> start_string) {
					if (ss >> end_string) {
						if (ss >> pawn_promote) {
							pawn_promote = tolower(pawn_promote);
							switch(pawn_promote){
								case 'q':
									promote_name_value = 5;
									break;
								case 'b':
									promote_name_value = 4;
									break;
								case 'r':
									promote_name_value = 3;
									break;
								case 'n':
									promote_name_value = 2;
									break;
							}
							if (promote_name_value != -1){
								if (proper_chess_move(start_string) && proper_chess_move(end_string)) {
									Moving move = Moving(chess_to_coord(start_string), chess_to_coord(end_string);
									game_state = board.call_move(move, promote_name_value, player_to_move);
								} else {
									std::cout << "Invalid move" << std::endl;
								}
							} else {
								std::cout << "Invalid promotion" << std::endl;
							}
						} else if (proper_chess_move(start_string) && proper_chess_move(end_string)) {
							Moving move = Moving(chess_to_coord(start_string), chess_to_coord(end_string);
							game_state = board.call_move(move, player_to_move);
						} else {
							std::cout << "Invalid move" << std::endl;
						}
					} else {
						std::cout << "Input a valid end position" << std::endl;
					}
				} else {
					game_state = board.call_move(player_to_move);
				}
				if (game_state == -2) {
					std::cout << "Move is not valid" << std::endl;
				} else if (game_state == -1) {
					black_turn = !black_turn;
				} else if (game_state >= 0) {
					if (game_state == 0) {
						std::cout << "Stalemate!" << std::cout;
						white_wins += 0.5;
						black_wins += 0.5;
					} else if (game_state == 1) {
						std::cout << "Checkmate! White wins!" << std::cout;
						white_wins++;
					} else if (game_state == 2) {
						std::cout << "Checkmate! Black wins!" << std::cout;
						black_wins++;
					}
					board.reset();
				}
				//if game_state == -3 then we pretend nothing happened

			} else if (input_string == "setup") {
				std::string setup_input;
				getline(std::cin, setup_input);
				board.reset();
				while (std::cin) {
					stringstream setup_ss{setup_input};
					std::string setup_first_input;
					if (setup_ss >> setup_first_input) {
						if (setup_first_input == "+") {
							std::string setup_second_input;
							if (setup_ss >> setup_second_input) {
								char setup_piece;
								std::string setup_posn;
								
								int setup_name_value;
								bool setup_is_black = true;
								Coord piece_coord;
								if (setup_ss >> setup_piece) {
									switch (setup_piece) {
										case 'k':
											setup_name_value = 6;
											break;
										case 'q':
											setup_name_value = 5;
											break;
										case 'b':
											setup_name_value = 4;
											break;
										case 'r':
											setup_name_value = 3;
											break;
										case 'n':
											setup_name_value = 2;
											break;
										case 'p':
											setup_name_value = 1;
											break;
										case 'K':
											setup_name_value = 6;
											setup_is_black = false;
											break;
										case 'Q':
											setup_name_value = 5;
											setup_is_black = false;
											break;
										case 'B':
											setup_name_value = 4;
											setup_is_black = false;
											break;
										case 'R':
											setup_name_value = 3;
											setup_is_black = false;
											break;
										case 'N':
											setup_name_value = 2;
											setup_is_black = false;
											break;
										case 'P':
											setup_name_value = 1;
											setup_is_black = false;
											break;
										default:
											setup_name_value = -1;
									}
								}
							if (setup_name_value >= 1) {
								if (proper_chess_move(setup_second_input)) {
									piece_coord = chess_to_coord(setup_second_input);
									board.place_piece(setup_name_value, piece_coord, setup_is_black);
								} else {
									std::cout << "Must input position as well" << std::endl;
								}
							} else {
								std::cout << "Invalid command" << std::endl;
							}
						}
					} else if (setup_first_input == "-") {
						std::string setup_second_input;
						if (setup_ss >> setup_second_input) {
							if (proper_chess_move(setup_second_input)) {
								board.remove_piece(piece_coord);
							} else {
								std::cout << "Invalid move" << std::endl;
							}
						} else {
							std::cout << "Must input position as well" << std::endl;
						}
					} else if (setup_first_input == "=") {
						std::string setup_second_input;
						if (setup_ss >> setup_second_input) {
							if(setup_second_input == "black") {
								black_turn = true;
							} else if (setup_second_input == "white") {
								black_turn = false;
							}
						} else {
							std::cout << "Must be black or white" << std::endl;
						}
					} else if (setup_first_input == "done") {
						int player_calc = (black_turn) ? 2 : 1;
						board.calc_all_valid_moves(player_calc);
					} else {
						std::cout << "Invalid command" << std::endl;
					}
				}
			} else {
				std::cout << "Invalid command" << std::endl;
			}
		} else if (std::cin.eof()) {
				std::cout << "Final Score:" << std::endl;
				std::cout << "White: " << white_wins << std::endl;
				std::cout << "Black: " << black_wins << std::endl;
			}
		}
	}
}
