#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <string_view>
#include <memory>

class Item
{
protected:
	const std::string m_Name;

	Item(const std::string& name) noexcept;
	Item(Item&& other) noexcept = delete;
public:
	const std::string& Name() const noexcept;
};

class Gun : public Item
{
private:
	const double m_MinDamage;
	const double m_MaxDamage;
	const char m_Rate;
public:
	Gun(const std::string& name, const double min, const double max, const char rate) noexcept;
	Gun(Gun&& other) noexcept = delete;

	double Damage() const noexcept;
};

enum class ItemType { gun };

class ItemFactory
{
private:
	inline static const std::unordered_map<ItemType, std::vector<std::string>> m_Types
	{
		{ItemType::gun, {"pistol", "shotgun", "katana", "minigun", "rocketlauncher"}}
	};

	inline static const std::unordered_map<ItemType, int> m_TypeLimits
	{
		{ItemType::gun, 2}
	};
public:
	ItemFactory() noexcept = delete;

	static ItemType TypeOf(std::string_view name) noexcept;
	static bool IsValid(std::string_view name) noexcept;
	static int LimitOf(const ItemType type) noexcept;
	static std::unique_ptr<Item> CreateItem(std::string_view name) noexcept;
};