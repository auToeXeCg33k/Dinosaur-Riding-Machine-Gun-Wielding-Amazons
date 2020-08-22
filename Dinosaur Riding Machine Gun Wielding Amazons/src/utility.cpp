#include "utility.h"

#include <iostream>

int ReadGameMode() noexcept
{
	std::cout << "Enter gamemode number: ";

	std::string input;
	int mode;

	while (1)
	{
		std::getline(std::cin, input);

		try
		{
			mode = stoi(input);

			if (mode < 1 || mode > 1)
			{
				std::cout << "Invalid gamemode. Try again: ";
				continue;
			}

			return mode;
		}

		catch (const std::invalid_argument&)
		{
			std::cout << "Not a number. Try again: ";
		}
	}
}

int CheckWin(GameData& data) noexcept
{
	if (!data.CurrentPlayer().alive() && data.CurrentPlayer().spawns() == data.MaxSpawns())
		return 1;

	if (!data.OtherPlayer().alive() && data.OtherPlayer().spawns() == data.MaxSpawns())
		return 2;

	return 0;
}

std::string toLower(const std::string& input) noexcept
{
	std::string ret;

	for (const auto& x : input)
		ret.push_back(std::tolower(x));

	return ret;
}

void ProcessInput(const std::string& input, std::vector<std::string>& words) noexcept
{
	std::string word;

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