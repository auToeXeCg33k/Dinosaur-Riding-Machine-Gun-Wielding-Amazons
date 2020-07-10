#pragma once


struct Point
{
	const char x;
	const char y;


	Point(const char x, const char y);


	bool operator==(const Point other) const;


	bool operator!=(const Point other) const;
};