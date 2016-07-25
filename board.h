#ifndef __BOARD_H__
#define __BOARD_H__

class Piece;
class Moving;

class Board {
                Piece* piece_array[][];
                std::vector<Piece*> black_pieces;
                std::vector<Piece*> white_pieces;
                std::vector<Moving> moves_made;
                std::vector<Piece*> destroy;
                std::vector<Moving> possible_moves;
				
				Controller * controller1;
				Controller * controller2;
				
				void calc_all_valid_moves(int player);
				bool isCheckingMove(const Moving &move);
				int end_of_game_check();
        public:
                Board();
                ~Board();
                void setBoard();
                void place_piece();
                void reset();
                void draw();
				std::vector<Moving> get_valid_moves(int player);
				Piece * get_piece(Coord posn);
				Piece * get_king(int player);
				void call_move(int player);
				void call_move(Moving move, int player);
				void call_move(Moving move, int name_value, int player);
				void add_players(int p1, int p2);
				void move_piece(Moving move, int type);
				void undo();
				Piece* get_piece(Coord posn);
				Piece* get_king(int player);
				vector<Piece*> get_player_pieces(int player);
				void remove_piece(Coord posn);
				
}

#endif
