#include "coord.h"

bool Coord::operator==(const Coord& rhs) const{
	return (x == rhs.x && y == rhs.y);
}
