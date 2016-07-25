#ifndef __HUMAN_H__
#define __HUMAN_H__

class Human(): public Controller{
public:
	Human(int player);
	bool move(Moving inputMove);
	bool move(Moving inputMove, int name) override;
};

#endif
