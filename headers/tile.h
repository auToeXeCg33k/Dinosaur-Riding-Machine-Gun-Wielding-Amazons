#pragma once
#include "amazon.h"
#include <unordered_set>


class Tile
{
private:
	std::unordered_set<Amazon*> amazons;
	std::vector<std::unique_ptr<Dino>> dinos;
	std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>> items;

public:
	Tile() noexcept;
	Tile(const Tile& other) noexcept = delete;
	Tile(Tile&& other) noexcept;

	void add(Amazon* amazon) noexcept;
	void add(std::unique_ptr<Item>&& item) noexcept;
	void add(std::unique_ptr<Dino>&& dino) noexcept;

	void remove(Amazon* amazon) noexcept;
	std::unique_ptr<Dino> remove(Dino* dino) noexcept;
	std::unique_ptr<Item> remove(std::string_view name) noexcept;

	bool has(Amazon* const amazon) const noexcept;
	bool has(Dino* const dino) const noexcept;
	bool has(std::string_view name) const noexcept;

	bool spawnDino() noexcept;
	bool spawnItem(std::string_view name) noexcept;
	
	const std::unordered_set<Amazon*>& AmazonContainer() const noexcept;
	const std::vector<std::unique_ptr<Dino>>& DinoContainer() const noexcept;
	const std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>>& ItemContainer() const noexcept;
};