vector<Moving> moves_made;
vector<Piece*> destroy;
void move_piece(Moving mov){
	moves_made.push_back(mov);
	destroy.push_back(piece_array[mov.end.y][mov.end.x]);
	piece_array[mov.end.y][move.end.x] = piece_array[mov.start.y][mov.start.x];
	piece_array[mov.start.y][mov.start.x] = nullptr;
	piece_array[mov.end.y][mov.end.x]->update_posn(mov.end);
}
void promote_move_piece(Moving mov){
	moves_made.push_back(mov);
	destroy.push_back(piece_array[mov.start.y][mov.start.x]);
	destory.push_back(nullptr);
}
void undo(){
	if(destroy.size()>moves_made.size()){
		delete piece_array[moves_made.back().end.y][moves_made.back().end.x];
		destroy.pop_back();
	}
	piece_array[moves_made.back().start.y][moves_made.back().start.x] = piece_array[moves_made.back().end.y][moves_made.back().end.x];
	piece_array[moves_made.back().end.y][moves_made.back().end.x] = destroy.back();
	moves_made.pop_back();
	destroy.pop_back();
}

Piece* get_piece(Coord posn){
	return piece_array[posn.y][posn.x];
}


