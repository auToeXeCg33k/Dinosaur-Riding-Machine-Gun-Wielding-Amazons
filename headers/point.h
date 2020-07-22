#pragma once


class Point
{
private:
	char cx;
	char cy;

public:
	Point() noexcept;
	Point(const char x, const char y) noexcept;
	Point(const Point& other) noexcept;
	Point(Point&& other) noexcept;

	char x() const noexcept;
	char y() const noexcept;
	
	bool operator==(const Point other) const noexcept;
	bool operator!=(const Point other) const noexcept;
	Point& operator=(const Point& other) noexcept;
	Point& operator=(Point&& other) noexcept;
};