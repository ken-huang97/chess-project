#ifndef __UNDOINFO_H__
#define __UNDOINFO_H__
#include <vector>
#include "moving.h"

struct undoInfo{
	Moving mov;
	vector<Piece*> destroy;
	int first_move_chk;
	int type_move;
};

#endif
