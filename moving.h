#ifndef __MOVING_H__
#define __MOVING_H__
#include "coord.h"

struct Moving{
	Coord start;
	Coord end;
	bool operator==(const Moving& rhs) const;
};

#endif
