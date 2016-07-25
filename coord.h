#ifndef __COORD_H__
#define __COORD_H__

struct Coord{
	int x,y;
	bool operator==(const Coord& rhs) const;
};

#endif

