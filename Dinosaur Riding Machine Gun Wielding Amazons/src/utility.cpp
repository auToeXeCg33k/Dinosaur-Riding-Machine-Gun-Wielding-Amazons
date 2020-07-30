#include <iostream>

#include "utility.h"

using std::move;
using std::string;
using std::string_view;
using std::cout;


Point::Point() noexcept : cx(0), cy(0) {}


Point::Point(const int x, const int y) noexcept : cx(x), cy(y) {}


Point::Point(const Point& other) noexcept : cx(other.cx), cy(other.cy) {}


Point::Point(Point&& other) noexcept : cx(move(other.cx)), cy(move(other.cy)) {}


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

	this->cx = move(other.cx);
	this->cy = move(other.cy);

	return *this;
}




int ReadGameMode() noexcept
{
	cout << "Enter gamemode number: ";

	string input;
	int mode;

	while (1)
	{
		std::getline(std::cin, input);

		try
		{
			mode = stoi(input);

			if (mode < 1 || mode > 1)
			{
				cout << "Invalid gamemode. Try again: ";
				continue;
			}

			return mode;
		}

		catch (const std::invalid_argument&)
		{
			cout << "Not a number. Try again: ";
		}
	}
}




char CheckWin(GameData& data) noexcept
{
	if (!data.CurrentPlayer().alive() && data.CurrentPlayer().spawns() == data.MaxSpawns())
		return 1;

	if (!data.OtherPlayer().alive() && data.OtherPlayer().spawns() == data.MaxSpawns())
		return 2;

	return 0;
}




string toLower(string_view input) noexcept
{
	string ret;

	for (const auto& x : input)
		ret.push_back(std::tolower(x));

	return ret;
}




void ProcessInput(string_view input, std::vector<string>& words) noexcept
{
	string word;

	for (size_t i = 0; i < input.length(); i++)
	{
		if (input.at(i) != ' ')
			word.push_back(input.at(i));

		if (i == input.length() - 1 && !word.empty())
		{
			words.push_back(word);
			break;
		}

		if (input.at(i) == ' ' && !word.empty())
		{
			words.push_back(word);
			word.clear();
		}
	}
}