#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

#include "player.h"


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


int ReadGameMode() noexcept;


int CheckWin(GameData& data) noexcept;


std::string toLower(const std::string& input) noexcept;


void ProcessInput(const std::string& input, std::vector<std::string>& words) noexcept;

#endif