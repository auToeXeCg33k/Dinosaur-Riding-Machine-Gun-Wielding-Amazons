#pragma once

#include <string>

class Amazon;
class Tile;
class GameData;

class BrainDrainer
{
private:
	const double m_MinDamage;
	const double m_MaxDamage;

	double Damage() const noexcept;

public:
	BrainDrainer() noexcept;
	BrainDrainer(BrainDrainer&& other) noexcept = delete;

	std::string Attack(Amazon& amazon, Tile& tile, GameData& data) const noexcept;
};