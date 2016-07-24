#ifndef __OBSERVER_H__
#define __OBSERVER_H__

struct Move;

class Observer{
  public:
	virtual notify(Move posn)=0;
	virtual ~Observer(){}
};

#endif