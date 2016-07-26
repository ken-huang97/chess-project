#ifndef __COMPUTER_H_
#define __COMPUTER_H_

class Moving;

class Computer:: public Controller{
	int level;
	bool is_capture_move(Moving move);
public:
	void move() override;
}
