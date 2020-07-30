#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

#include "item.h"


class Dino
{
private:
	double hp;
	bool bTamed;

public:
	Dino() noexcept;
	Dino(Dino&& other) noexcept = delete;

	double health() const noexcept;
	void health(double const hp) noexcept;

	bool tamed() const noexcept;
	void tamed(bool const tmd) noexcept;
};


class Amazon
{
private:
	const std::string sName;
	double hp;
	std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>> inv;
	Gun* held;
	Dino* pDino;
	std::unique_ptr<Dino> pRiding;

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
	void hand(Gun* const item) noexcept;

	Dino* dino() const noexcept;
	void dino(Dino* const dino) noexcept;

	std::unique_ptr<Dino>& riding() noexcept;
	void riding(std::unique_ptr<Dino>&& dino) noexcept;

};


class BrainDrainer
{
private:
	const double min;
	const double max;

	double damage() const noexcept;

public:
	BrainDrainer() noexcept;
	BrainDrainer(BrainDrainer&& other) noexcept = delete;

	std::string attack(Amazon& amazon) const noexcept;
};

#endif