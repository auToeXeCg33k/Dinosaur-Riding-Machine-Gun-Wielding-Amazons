#include "commandhandler.h"
#include "utility.h"
#include "wincheck.h"
#include <iostream>

using namespace std;


int main()
{
	const int gameMode(ReadGameMode());

	const CommandHandler handler;
	GameData data(gameMode);
	Map map(gameMode);

	cout << "\nMap size is " << map.size() << "x" << map.size() << ".\n"
		"The maximum number of actions per turn is " << data.MaxActions() << ".\n"
		"The maximum number of spawns is " << data.MaxSpawns() << ".\n"
		"The maximum number of living amazons is " << data.MaxAlive() << ".\n"
		"To open the help menu, type \"help\"!\n" << endl;;

	string input;
	vector<string> words;

	while (1)
	{
		cout << data.CurrentPlayer().name() << ": ";
		getline(cin, input);

		words.clear();

		ProcessInput(input, words);

		if (words.size() == 0)
			continue;

		if (words.at(0) == "exit")
			return 0;

		cout << '\n' << handler.handleCommand(words, map, data) << endl;

		switch (CheckWin(data))
		{
		case 2:
			cout << data.CurrentPlayer().name() << " won! GG" << endl;
			return 0;

		case 1:
			cout << data.OtherPlayer().name() << " won! GG" << endl;
			return 0;
		}
	}
}