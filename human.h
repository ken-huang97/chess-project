#ifndef __HUMAN_H__
#define __HUMAN_H__

class Human(): public Controller{
public:
	Human(int player);
	bool move(Moving inputMove) override;
	bool move(Moving inputMove, int name) override;
};

#endif
