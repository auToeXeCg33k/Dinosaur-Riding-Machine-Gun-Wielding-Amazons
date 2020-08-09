#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>


class Item
{
protected:
	const std::string nm;
	Item(const std::string& name) noexcept;
	Item(Item&& other) noexcept = delete;

public:
	const std::string& name() const noexcept;
};


class Gun : public Item
{
private:
	const double min;
	const double max;
	const char rate;

public:
	Gun(const std::string& name, const double min, const double max, const char rate) noexcept;
	Gun(Gun&& other) noexcept = delete;
	double dmg() const noexcept;
};


enum class ItemType { gun };


class ItemFactory
{
private:
	static const std::unordered_map<ItemType, std::vector<std::string>> types;
	static const std::unordered_map<ItemType, int> typeLimits;

public:
	ItemFactory() noexcept = delete;
	static ItemType TypeOf(std::string_view name) noexcept;
	static bool IsValid(std::string_view name) noexcept;
	static int LimitOf(const ItemType type) noexcept;
	static std::unique_ptr<Item> CreateItem(std::string_view name) noexcept;
};

#endif