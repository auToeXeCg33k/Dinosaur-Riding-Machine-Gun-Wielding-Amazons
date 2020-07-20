#include "point.h"
#include <utility>


Point::Point(const char x, const char y) noexcept : cx(x), cy(y) {}


Point::Point(const Point& other) noexcept : cx(other.cx), cy(other.cy) {}


Point::Point(Point&& other) noexcept : cx(std::move(other.cx)), cy(std::move(other.cy)) {}


char Point::x() const noexcept
{
	return cx;
}


char Point::y() const noexcept
{
	return cy;
}


bool Point::operator==(const Point other) const noexcept
{
	return cx == other.cx && cy == other.cy;
}


bool Point::operator!=(const Point other) const noexcept
{
	return cx != other.cx || cy != other.cy;
}


Point& Point::operator=(Point&& other) noexcept
{
	this->cx = std::move(other.cx);
	this->cy = std::move(other.cy);
	return *this;
}