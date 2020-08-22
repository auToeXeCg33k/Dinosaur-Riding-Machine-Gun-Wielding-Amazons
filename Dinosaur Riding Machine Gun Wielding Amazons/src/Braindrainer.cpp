#include "Braindrainer.h"

#include "Amazon.h"
#include "Map.h"
#include "GameData.h"

#include <random>

BrainDrainer::BrainDrainer() noexcept
	: m_MinDamage{ 60.0 }, m_MaxDamage{ 90.0 } {}

double BrainDrainer::Damage() const noexcept
{
	std::mt19937_64 mt{ std::random_device{}() };
	std::uniform_real_distribution<> dist{ 0, 1 };

	return (m_MaxDamage - m_MinDamage) * dist(mt) + m_MinDamage;
}

std::string BrainDrainer::Attack(Amazon& amazon, Map& map, GameData& data) const noexcept
{
	auto dmg{ Damage() };

	if (amazon.riding())
	{
		if (amazon.dino()->Health() - dmg < 0.0)
		{
			amazon.dino()->Health(0.0);
			map.tile(map.find(data.CurrentPlayer().selected())).add(std::move(data.CurrentPlayer().selected()->riding()));
		}
		else
			amazon.dino()->Health(amazon.dino()->Health() - dmg);

		if (!amazon.dino()->Health())
			return amazon.name() + "'s dino was killed by a Braindrainer.\n";

		return amazon.name() + "'s dino suffered " + std::to_string(static_cast<int>(round(dmg))) + " points of damage from a Braindrainer.\n";
	}

	if (amazon.health() - dmg < 0.0)
	{
		amazon.health(0.0);
		data.CurrentPlayer().decAlive();
	}
	else
		amazon.health(amazon.health() - dmg);

	if (!amazon.health())
		return amazon.name() + " was killed by a Braindrainer.\n";

	return amazon.name() + " suffered " + std::to_string(static_cast<int>(round(dmg))) + " points of damage from a Braindrainer.\n";
}