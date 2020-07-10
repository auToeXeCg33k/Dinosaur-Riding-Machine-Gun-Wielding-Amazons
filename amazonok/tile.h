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
	Tile();
	Tile(Tile&& other) noexcept;
	void add(Amazon* amazon);
	void add(std::unique_ptr<Dino>&& dino);
	void add(std::unique_ptr<Item>&& item);
	void remove(Amazon* amazon);
	std::unique_ptr<Dino> remove(Dino* dino);
	std::unique_ptr<Item> remove(std::string_view name);
	bool is_here(Amazon* amazon);
	bool has(std::string_view name);
	bool spawnDino();
	bool spawnItem(std::string_view name);
	const std::unordered_set<Amazon*>& AmazonContainer() const;
	const std::vector<std::unique_ptr<Dino>>& DinoContainer() const;
	const std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>>& ItemContainer() const;
};