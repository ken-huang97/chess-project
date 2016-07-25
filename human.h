#ifndef __HUMAN_H__
#define __HUMAN_H__

class Human(): public Controller{
public:
	Human(int player);
	void move(Moving inputMove);
	void move(Moving inputMove, int name) override;
};

#endif
