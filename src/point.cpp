#include "point.h"
#include <utility>


Point::Point() noexcept : cx(0), cy(0) {}


Point::Point(const int x, const int y) noexcept : cx(x), cy(y) {}


Point::Point(const Point& other) noexcept : cx(other.cx), cy(other.cy) {}


Point::Point(Point&& other) noexcept : cx(std::move(other.cx)), cy(std::move(other.cy)) {}


int Point::x() const noexcept
{
	return cx;
}


int Point::y() const noexcept
{
	return cy;
}


bool Point::operator==(const Point& other) const noexcept
{
	return cx == other.cx && cy == other.cy;
}


bool Point::operator!=(const Point& other) const noexcept
{
	return cx != other.cx || cy != other.cy;
}


Point& Point::operator=(const Point& other) noexcept
{
	if (&other == this)
		return *this;

	cx = other.cx;
	cy = other.cy;

	return *this;
}



Point& Point::operator=(Point&& other) noexcept
{
	if (&other == this)
		return *this;
	
	this->cx = std::move(other.cx);
	this->cy = std::move(other.cy);
	
	return *this;
}