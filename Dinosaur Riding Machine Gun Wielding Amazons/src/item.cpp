#include <random>

#include "item.h"

using std::string;
using std::string_view;
using std::unordered_map;
using std::make_unique;


Item::Item(const string& name) noexcept : nm{ name } {}


const std::string& Item::name() const noexcept
{
	return nm;
}




Gun::Gun(const string& name, const double min, const double max, const char rate) noexcept : Item{ name }, min{ min }, max{ max }, rate{ rate } {}


double Gun::dmg() const noexcept
{
	std::mt19937_64 mt{ std::random_device{}() };
	std::uniform_real_distribution<> dist{ 0, 1 };

	double dmg{ 0.0 };

	for (int i = 0; i < rate; i++)
		dmg += (max - min) * dist(mt) + min;

	return dmg;
}




const unordered_map<ItemType, std::vector<std::string>> ItemFactory::types
{
	{ItemType::gun, {"pistol", "shotgun", "katana", "minigun", "rocketlauncher"}}
};


const unordered_map<ItemType, int> ItemFactory::typeLimits
{
	{ItemType::gun, 2}
};


ItemType ItemFactory::TypeOf(string_view name) noexcept
{
	for (const auto& x : types)
		for (const auto& y : x.second)
			if (y == name)
				return x.first;
}


bool ItemFactory::IsValid(string_view name) noexcept
{
	for (const auto& x : types)
		for (const auto& y : x.second)
			if (y == name)
				return true;

	return false;
}


int ItemFactory::LimitOf(const ItemType type) noexcept
{
	return typeLimits.at(type);
}


std::unique_ptr<Item> ItemFactory::CreateItem(string_view name) noexcept
{
	if (name == "pistol")
		return make_unique<Gun>("pistol", 15.0, 20.0, 2);

	if (name == "shotgun")
		return make_unique<Gun>("shotgun", 50.0, 75.0, 1);

	if (name == "katana")
		return make_unique<Gun>("katana", 20.0, 30.0, 3);

	if (name == "minigun")
		return make_unique<Gun>("minigun", 1.5, 5.0, 30);

	if (name == "rocketlauncher")
		return make_unique<Gun>("rocketlauncher", 90.0, 120.0, 1);
}