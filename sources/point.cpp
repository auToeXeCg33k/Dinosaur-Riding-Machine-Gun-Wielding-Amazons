#include "point.h"
#include <utility>


Point::Point(const char x, const char y) noexcept : x(x), y(y) {}

Point::Point(const Point& other) noexcept : x(other.x), y(other.y) {}

Point::Point(Point&& other) noexcept : x(std::move(other.x)), y(std::move(other.y)) {}

bool Point::operator==(const Point other) const noexcept
{
	return x == other.x && y == other.y;
}


bool Point::operator!=(const Point other) const noexcept
{
	return x != other.x || y != other.y;
}