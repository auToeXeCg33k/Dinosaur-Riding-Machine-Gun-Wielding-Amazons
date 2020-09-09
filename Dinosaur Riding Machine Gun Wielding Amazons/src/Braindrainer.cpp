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

std::string BrainDrainer::Attack(Amazon& amazon, Tile& tile, GameData& data) const noexcept
{
	auto dmg{ Damage() };

	if (amazon.riding())
	{
		if (amazon.dino()->Health() - dmg <= 0.0)
		{
			amazon.dino()->Health(0.0);
			tile.add(std::move(amazon.riding()));
			return amazon.name() + "'s dino was killed by a Braindrainer.\n";
		}

		amazon.dino()->Health(amazon.dino()->Health() - dmg);
		return amazon.name() + "'s dino suffered " + std::to_string(static_cast<int>(round(dmg))) + " points of damage from a Braindrainer.\n";
	}

	if (amazon.health() - dmg <= 0.0)
	{
		amazon.health(0.0);

		if (data.CurrentPlayer().existsAmazon(amazon.name()) && &data.CurrentPlayer().getAmazon(amazon.name()) == &amazon)
			data.CurrentPlayer().decAlive();
		else
			data.OtherPlayer().decAlive();

		return amazon.name() + " was killed by a Braindrainer.\n";
	}
	
	amazon.health(amazon.health() - dmg);
	return amazon.name() + " suffered " + std::to_string(static_cast<int>(round(dmg))) + " points of damage from a Braindrainer.\n";
}