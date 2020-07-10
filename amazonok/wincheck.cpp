#include "wincheck.h"

using namespace std;


char CheckWin(GameData& data)
{
	if (!data.CurrentPlayer().alive() && data.CurrentPlayer().spawns() == data.MaxSpawns())
		return 1;

	if (!data.OtherPlayer().alive() && data.OtherPlayer().spawns() == data.MaxSpawns())
		return 2;

	return 0;
}