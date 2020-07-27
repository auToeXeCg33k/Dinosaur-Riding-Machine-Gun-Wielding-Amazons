#include "gamedata.h"

using namespace std;


GameData::GameData(int i) noexcept : p1("Player 1"), p2("Player 2"), active(false), nMaxActions(i == 1 ? 3 : 3), nMaxSpawns(i == 1 ? 6 : 6), nMaxAlive(i == 1 ? 3 : 3) {}


Player& GameData::CurrentPlayer() noexcept
{
	return active ? p2 : p1;
}


Player& GameData::OtherPlayer() noexcept
{
	return active ? p1 : p2;
}


unsigned GameData::MaxActions() const noexcept
{
	return nMaxActions;
}


unsigned GameData::MaxSpawns() const noexcept
{
	return nMaxSpawns;
}


unsigned GameData::MaxAlive() const noexcept
{
	return nMaxAlive;
}


void GameData::turn() noexcept
{
	active = !active;
	p1.resetActions();
	p2.resetActions();
}