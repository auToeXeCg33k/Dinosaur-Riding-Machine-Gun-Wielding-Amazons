#include "item.h"
#include <random>

using namespace std;


Item::Item(std::string_view name) : name(name) {}


const std::string& Item::get_name()
{
	return name;
}


Gun::Gun(string_view name, const double min, const double max, const int rate) : Item(name), min(min), max(max), rate(rate) {}


double Gun::get_dmg()
{
	random_device rd;
	mt19937_64 mt(rd());
	uniform_real_distribution<> dist(0, 1);

	double dmg = 0.0;

	for (int i = 0; i < rate; i++)
		dmg += (max - min) * dist(mt) + min;

	return dmg;
}


const unordered_map<ItemType, vector<string>> ItemFactory::types
{
	{ItemType::gun, {"pistol", "shotgun", "katana", "minigun", "rocket"}}
};


const unordered_map<ItemType, int> ItemFactory::typeLimits
{
	{ItemType::gun, 2}
};


ItemType ItemFactory::lookUp(string_view name)
{
	for (auto x : types)
		for (auto y : x.second)
			if (y == name)
				return x.first;
}


bool ItemFactory::isValid(string_view name)
{
	for (auto x : types)
		for (auto y : x.second)
			if (y == name)
				return true;
	return false;
}


int ItemFactory::typeLimit(const ItemType type)
{
	return typeLimits.at(type);
}


unique_ptr<Item> ItemFactory::CreateItem(string_view name)
{
	if (name == "pistol")
		return make_unique<Gun>("pistol", 15.0, 20.0, 2);

	if (name == "shotgun")
		return make_unique<Gun>("shotgun", 50.0, 75.0, 1);

	if (name == "katana")
		return make_unique<Gun>("katana", 20.0, 30.0, 3);

	if (name == "minigun")
		return make_unique<Gun>("minigun", 1.5, 5.0, 30);

	if (name == "rocket")
		return make_unique<Gun>("rocket", 90.0, 120.0, 1);
}