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
	GameData(int i) noexcept;
	GameData(GameData&& other) noexcept = delete;

	Player& CurrentPlayer() noexcept;
	Player& OtherPlayer() noexcept;

	int MaxActions() const noexcept;
	int MaxSpawns() const noexcept;
	int MaxAlive() const noexcept;
	
	void turn() noexcept;
};