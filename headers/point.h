#pragma once


struct Point
{
	const char x;
	const char y;

	Point(const char x, const char y) noexcept;
	Point(const Point& other) noexcept;
	Point(Point&& other) noexcept;
	
	bool operator==(const Point other) const noexcept;
	bool operator!=(const Point other) const noexcept;
};