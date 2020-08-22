#pragma once

#include <string>

class Amazon;
class Map;
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

	std::string Attack(Amazon& amazon, Map& map, GameData& data) const noexcept;
};