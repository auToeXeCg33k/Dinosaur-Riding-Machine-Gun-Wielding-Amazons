#pragma once


class Point
{
private:
	int cx;
	int cy;

public:
	Point() noexcept;
	Point(const int x, const int y) noexcept;
	Point(const Point& other) noexcept;
	Point(Point&& other) noexcept;

	int x() const noexcept;
	int y() const noexcept;
	
	bool operator==(const Point& other) const noexcept;
	bool operator!=(const Point& other) const noexcept;
	Point& operator=(const Point& other) noexcept;
	Point& operator=(Point&& other) noexcept;
};