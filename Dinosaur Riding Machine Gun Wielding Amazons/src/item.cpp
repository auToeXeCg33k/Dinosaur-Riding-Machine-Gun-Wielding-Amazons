#include "Item.h"

#include <random>

Item::Item(const std::string& name) noexcept
	: m_Name{ name } {}

const std::string& Item::Name() const noexcept { return m_Name; }

Gun::Gun(const std::string& name, const double min, const double max, const char rate) noexcept
	: Item{ name }, m_MinDamage{ min }, m_MaxDamage{ max }, m_Rate{ rate } {}

double Gun::Damage() const noexcept
{
	std::mt19937_64 mt{ std::random_device{}() };
	std::uniform_real_distribution<> dist{ 0, 1 };

	double dmg{ 0.0 };

	for (int i = 0; i < m_Rate; i++)
		dmg += (m_MaxDamage - m_MinDamage) * dist(mt) + m_MinDamage;

	return dmg;
}

ItemType ItemFactory::TypeOf(std::string_view name) noexcept
{
	for (const auto& x : m_Types)
		for (const auto& y : x.second)
			if (y == name)
				return x.first;
}

bool ItemFactory::IsValid(std::string_view name) noexcept
{
	for (const auto& x : m_Types)
		for (const auto& y : x.second)
			if (y == name)
				return true;

	return false;
}

int ItemFactory::LimitOf(const ItemType type) noexcept { return m_TypeLimits.at(type); }

std::unique_ptr<Item> ItemFactory::CreateItem(std::string_view name) noexcept
{
	if (name == "pistol")
		return std::make_unique<Gun>("pistol", 15.0, 20.0, 2);

	if (name == "shotgun")
		return std::make_unique<Gun>("shotgun", 50.0, 75.0, 1);

	if (name == "katana")
		return std::make_unique<Gun>("katana", 20.0, 30.0, 3);

	if (name == "minigun")
		return std::make_unique<Gun>("minigun", 1.5, 5.0, 30);

	if (name == "rocketlauncher")
		return std::make_unique<Gun>("rocketlauncher", 90.0, 120.0, 1);
}