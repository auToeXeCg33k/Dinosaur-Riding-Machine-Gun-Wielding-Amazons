#pragma once
#include "amazon.h"
#include <unordered_set>
#include <forward_list>

class Tile
{
private:
	std::unordered_set<Amazon*> amazons;
	std::unordered_set<std::unique_ptr<Dino>> dinos;
	std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>> items;

public:
	Tile();
	Tile(Tile&& other) noexcept;
	bool has(std::string_view name);
	void add(std::unique_ptr<Item>&& item);
	std::unique_ptr<Item> remove(std::string_view name);
	bool spawnDino();
	bool spawnItem(std::string_view name);
	void place(Amazon* amazon);
	void remove(Amazon* amazon);
	bool is_here(Amazon* amazon);
	std::forward_list<Amazon*> amazon_list() const;
	std::forward_list<Dino*> dino_list() const;
	std::forward_list<Item*> item_list() const;
};