#include "gamedata.h"

using namespace std;


GameData::GameData(int i) : p1("Player 1"), p2("Player 2"), active(false), nMaxActions(i == 1 ? 3 : 3), nMaxSpawns(i == 1 ? 6 : 6), nMaxAlive(i == 1 ? 3 : 3) {}


Player& GameData::CurrentPlayer()
{
	return active ? p2 : p1;
}


Player& GameData::OtherPlayer()
{
	return active ? p1 : p2;
}


int GameData::MaxActions()
{
	return nMaxActions;
}


int GameData::MaxSpawns()
{
	return nMaxSpawns;
}


int GameData::MaxAlive()
{
	return nMaxAlive;
}


void GameData::turn()
{
	active = !active;
	p1.actions() = 0;
	p2.actions() = 0;
}