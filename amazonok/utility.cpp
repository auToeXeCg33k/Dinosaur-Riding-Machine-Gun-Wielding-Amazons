#include "utility.h"
#include <iostream>

using namespace std;



int ReadGameMode()
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


void ProcessInput(string_view input, vector<string>& words)
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