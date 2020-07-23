#pragma once
#include "tile.h"
#include "point.h"

class Map
{
private:
	std::vector<std::vector<Tile>> tiles;
	int sz;

public:
	Map(const int i) noexcept;
	Map(Map&&) noexcept = delete;
	
	Tile& tile(const Point p) noexcept;

	int size() const noexcept;

	Point find(Amazon* const amazon) const noexcept;
};