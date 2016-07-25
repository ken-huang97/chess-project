#include "moving.h"

bool Moving::operator==(const Moving& rhs) const{
	return (start == rhs.start && end == rhs.end);
}
