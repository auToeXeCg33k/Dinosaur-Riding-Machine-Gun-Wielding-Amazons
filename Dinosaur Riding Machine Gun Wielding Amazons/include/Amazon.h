#pragma once

#include "Dino.h"
#include "Item.h"

#include <string>

class Amazon
{
private:
	const std::string m_Name;
	double m_HP;
	std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>> m_Inventory;
	Gun* m_Hand;
	Dino* m_Dino;
	std::unique_ptr<Dino> m_Ridden;
public:
	Amazon(std::string_view name) noexcept;
	Amazon(Amazon&& other) noexcept = delete;

	bool hasFreeSlot(const ItemType type) const noexcept;
	bool hasItem(std::string_view name) const noexcept;

	void take(std::unique_ptr<Item>&& item) noexcept;
	std::unique_ptr<Item> drop(std::string_view name) noexcept;
	Item* item(std::string_view name) const noexcept;

	const std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>>& inventory() const noexcept;

	const std::string& name() const noexcept;

	double health() const noexcept;
	void health(double const hp) noexcept;

	Gun* hand() const noexcept;
	void hand(Gun* const gun) noexcept;

	Dino* dino() const noexcept;
	void dino(Dino* const dino) noexcept;

	std::unique_ptr<Dino>& riding() noexcept;
	void riding(std::unique_ptr<Dino>&& dino) noexcept;
};