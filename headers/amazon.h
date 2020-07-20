#pragma once

#include "dino.h"
#include "item.h"

class Amazon
{
private:
	const std::string sName;
	double hp;
	std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>> inventory;
	Gun* held;
	Dino* pDino;
	std::unique_ptr<Dino> pRiding;

public:
	Amazon(std::string_view name) noexcept;
	Amazon(const Amazon& other) noexcept = delete;
	Amazon(Amazon&& other) noexcept;

	bool hasFreeSlot(const ItemType type) const noexcept;
	bool hasItem(std::string_view name) const noexcept;

	void take(std::unique_ptr<Item>&& item) noexcept;
	std::unique_ptr<Item> drop(std::string_view name) noexcept;
	Item* item(std::string_view name) const noexcept;

	const std::string& name() const noexcept;
	
	double health() const noexcept;
	void health(double const hp) noexcept;

	Gun* hand() const noexcept;
	void hand(Gun* const item) noexcept;

	Dino* dino() const noexcept;
	void dino(Dino* const dino) noexcept;

	std::unique_ptr<Dino>& riding() noexcept;
	void riding(std::unique_ptr<Dino>&& dino) noexcept;

};