#include "point.h"


Point::Point(const char x, const char y) : x(x), y(y) {}


bool Point::operator==(const Point other) const
{
	return x == other.x && y == other.y;
}


bool Point::operator!=(const Point other) const
{
	return x != other.x || y != other.y;
}