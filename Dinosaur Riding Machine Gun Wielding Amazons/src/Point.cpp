#include "Point.h"

#include <utility>

Point::Point() noexcept
	: m_X{ 0 }, m_Y{ 0 } {}

Point::Point(const int x, const int y) noexcept
	: m_X{ x }, m_Y{ y } {}

Point::Point(const Point& other) noexcept
	: m_X{ other.m_X }, m_Y{ other.m_Y } {}

Point::Point(Point&& other) noexcept
	: m_X{ std::move(other.m_X) }, m_Y{ std::move(other.m_Y) } {}

int Point::x() const noexcept { return m_X; }

int Point::y() const noexcept { return m_Y; }

bool Point::operator==(const Point& other) const noexcept { return m_X == other.m_X && m_Y == other.m_Y; }

bool Point::operator!=(const Point& other) const noexcept { return m_X != other.m_X || m_Y != other.m_Y; }

Point& Point::operator=(const Point& other) noexcept
{
	if (&other == this)
		return *this;

	m_X = other.m_X;
	m_Y = other.m_Y;

	return *this;
}

Point& Point::operator=(Point&& other) noexcept
{
	if (&other == this)
		return *this;

	this->m_X = std::move(other.m_X);
	this->m_Y = std::move(other.m_Y);

	return *this;
}