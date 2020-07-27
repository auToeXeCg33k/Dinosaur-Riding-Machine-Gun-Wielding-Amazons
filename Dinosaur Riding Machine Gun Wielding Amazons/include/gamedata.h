#pragma once

#include "player.h"

class GameData
{
private:
	Player p1;
	Player p2;
	bool active;
	const unsigned nMaxActions;
	const unsigned nMaxSpawns;
	const unsigned nMaxAlive;

public:
	GameData(int i) noexcept;
	GameData(GameData&& other) noexcept = delete;

	Player& CurrentPlayer() noexcept;
	Player& OtherPlayer() noexcept;

	unsigned MaxActions() const noexcept;
	unsigned MaxSpawns() const noexcept;
	unsigned MaxAlive() const noexcept;
	
	void turn() noexcept;
};