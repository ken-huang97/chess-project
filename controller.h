#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

class Board;

class Controller {
	Board *board;
	int player;
public:
	virtual move()=0;
	Controller(Board *board, int player);
	virtual ~Controller()=0;
}

#endif