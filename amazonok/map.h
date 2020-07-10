#pragma once
#include "tile.h"
#include "point.h"

class Map
{
private:
	std::vector<std::vector<Tile>> tiles;
	int size;

public:
	Map(const int i);
	Tile& tile(const char y, const char x);
	Tile& tile(const Point p);
	int get_size();
	Point location(Amazon* amazon);
};