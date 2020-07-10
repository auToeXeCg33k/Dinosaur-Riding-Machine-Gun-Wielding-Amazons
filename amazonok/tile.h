#pragma once
#include "amazon.h"
#include <unordered_set>
#include <forward_list>

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
	std::forward_list<Amazon*> amazon_list() const;
	std::forward_list<Dino*> dino_list() const;
	std::forward_list<Item*> item_list() const;
};