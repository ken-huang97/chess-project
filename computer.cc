Computer::Computer(int level): level{level}

Computer::move(Moving move) {
	int enemy = (player == 1) ? 2 : 1;
	std::vector<vector<Moving>> move_priority;
	move_priority.push_back(get_valid_moves(enemy));
	
	
	//
	
	//I think we can use pImpl to make this prettier?
	if (level >= 2) {
		vector<Moving> checks_or_captures;
		vector<Moving> checks_and_captures;
		
		//Method 1
		//Pyramid
		for (int i = 0; i < move_priority[0].size(); i++) {
			Moving temp = move_priority[0][i];
			if (temp == /*check move*/) {
				checks_or_captures.push_back(temp);
				if (temp == /*capture move*/) {
					checks_and_captures.push_back(temp);
				}
			} else if (temp == /*capture move */) {
				checks_or_captures.push_back(temp);
			}
		}
		
		//Method 2
		//Disjoint
		for (int i = 0; i < move_priority[0].size(); i++) {
			if (move_priority[0][i] == /*check move*/) {		
				if (move_priority[0][i] == /*capture move*/) {
					checks_and_captures.push_back(move_priority[0][i]);
				} else {
					checks_or_captures.push_back(move_priority[0][i]);
				}
			} else if (move_priority[0][i] == /*capture move */) {
				checks_or_captures.push_back(move_priority[0][i]);
			}
		}
		
		
		if (!checks_or_captures.empty()) move_priority.push_back(checks_or_captures);
		if (!checks_and_captures.empty()) move_priority.push_back(checks_and_captures);
	} 
	
	if (level >= 3) {
		vector<Moving> safe;
		vector<Moving> safe_and_ch_or_ca;
		vector<Moving> safe_and_ch_and_ca;
		
		//Method 2 continued
		for (int i = 0; i < move_priority[0].size(); i++) {
			Moving temp = move_priority[0][i];
			if (temp == /* safe */) {
				safe.push_back(temp);
			}
		}
		for (int i = 0; i < move_priority[1].size(); i++) {
			Moving temp = move_priority[1][i];
			if (temp == /* safe */) {
				safe_and_ch_or_ca.push_back(temp);
			}
		}
		for (int i = 0; i < move_priority[2].size(); i++) {
			Moving temp = move_priority[2][i];
			if (temp == /* safe */) {
				safe_and_ch_and_ca.push_back(temp);
			}
		}
		if (!safe.empty()) move_priority.push_back(safe);
		if (!safe_and_ch_or_ca.empty()) move_priority.push_back(safe_and_ch_or_ca);
		if (!safe_and_ch_and_ca.empty()) move_priority.push_back(safe_and_ch_and_ca);
	}
	if (level >= 4) {
		/* black magic */
	}
	
	
	
}