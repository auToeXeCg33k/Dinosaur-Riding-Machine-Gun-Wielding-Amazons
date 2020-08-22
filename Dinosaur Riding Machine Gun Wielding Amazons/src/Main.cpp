#include <iostream>

#include "utility.h"
#include "map.h"
#include "command.h"

int main()
{
	const int gameMode{ ReadGameMode() };

	GameData data{ gameMode };
	Map map{ gameMode };

	std::cout << "\nMap size is " << map.size() << "x" << map.size() << ".\n"
		"The maximum number of actions per turn is " << data.MaxActions() << ".\n"
		"The maximum number of spawns is " << data.MaxSpawns() << ".\n"
		"The maximum number of living amazons is " << data.MaxAlive() << ".\n"
		"To open the help menu, type \"help\"!\n" << std::endl;;

	std::string input;
	std::vector<std::string> words;

	while (1)
	{
		std::cout << data.CurrentPlayer().name() << ": ";
		std::getline(std::cin, input);

		words.clear();

		ProcessInput(input, words);

		if (words.size() == 0)
			continue;

		if (words.at(0) == "exit")
			return 0;

		std::cout << '\n' << CommandHandler::Instance().HandleCommand(words, map, data) << std::endl;

		switch (CheckWin(data))
		{
		case 2:
			std::cout << data.CurrentPlayer().name() << " won! GG" << std::endl;
			return 0;

		case 1:
			std::cout << data.OtherPlayer().name() << " won! GG" << std::endl;
			return 0;
		}
	}
}