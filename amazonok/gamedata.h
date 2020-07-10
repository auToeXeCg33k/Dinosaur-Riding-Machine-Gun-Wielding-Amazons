#pragma once
#include "player.h"


class GameData
{
private:
	Player p1;
	Player p2;
	bool active;
	const int nMaxActions;
	const int nMaxSpawns;
	const int nMaxAlive;

public:
	GameData(int i);
	Player& CurrentPlayer();
	Player& OtherPlayer();
	int MaxActions();
	int MaxSpawns();
	int MaxAlive();
	void turn();
};