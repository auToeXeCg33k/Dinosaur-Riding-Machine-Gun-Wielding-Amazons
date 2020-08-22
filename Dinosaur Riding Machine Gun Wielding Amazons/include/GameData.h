#pragma once

#include "Player.h"

class GameData
{
private:
	Player m_Player1;
	Player m_Player2;
	bool m_ActivePlayer;
	const unsigned m_MaxActions;
	const unsigned m_MaxSpawns;
	const unsigned m_MaxAlive;
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