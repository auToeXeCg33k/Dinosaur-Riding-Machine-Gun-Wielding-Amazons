#include "utility.h"
#include <iostream>
#include <cctype>


std::string toLower(std::string_view input) noexcept
{
	std::string ret;

	for (const auto& x : input)
		ret.push_back(std::tolower(x));

	return ret;
}


using namespace std;


int ReadGameMode() noexcept
{
	cout << "Enter gamemode number: ";

	string input;
	int mode;

	while (1)
	{
		getline(cin, input);

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

		catch (const invalid_argument&)
		{
			cout << "Not a number. Try again: ";
		}
	}
}


void ProcessInput(string_view input, vector<string>& words) noexcept
{
	string word;

	for (int i = 0; i < input.length(); i++)
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