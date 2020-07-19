#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>


class Item
{
protected:
	const std::string name;
	Item(std::string_view name);

public:
	const std::string& get_name();
};


class Gun : public Item
{
private:
	const double min;
	const double max;
	const char rate;

public:
	Gun(std::string_view name, const double min, const double max, const int rate);
	double get_dmg();
};


enum class ItemType { gun };


class ItemFactory
{
private:
	static const std::unordered_map<ItemType, std::vector<std::string>> types;
	static const std::unordered_map<ItemType, int> typeLimits;

public:
	static ItemType lookUp(std::string_view name);
	static bool isValid(std::string_view name);
	static int typeLimit(const ItemType type);
	static std::unique_ptr<Item> CreateItem(std::string_view name);
};