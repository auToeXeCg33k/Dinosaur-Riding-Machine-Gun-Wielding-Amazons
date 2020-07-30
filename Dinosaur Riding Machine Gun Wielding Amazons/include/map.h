#ifndef MAP_H
#define MAP_H

#include <unordered_set>

#include "character.h"
#include "utility.h"


class Tile
{
private:
	std::unordered_set<Amazon*> amazons;
	std::vector<std::unique_ptr<Dino>> dinos;
	std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>> items;
	std::unique_ptr<BrainDrainer> drainer;

public:
	Tile() noexcept;
	Tile(const Tile& other) noexcept = delete;
	Tile(Tile&& other) noexcept;

	Tile& operator=(const Tile& other) noexcept = delete;
	Tile& operator=(Tile&& other) noexcept = delete;

	void add(Amazon* const amazon) noexcept;
	void add(std::unique_ptr<Item>&& item) noexcept;
	void add(std::unique_ptr<Dino>&& dino) noexcept;
	void add(std::unique_ptr<BrainDrainer>&& drainer) noexcept;

	void remove(Amazon* const amazon) noexcept;
	std::unique_ptr<Dino> remove(Dino* dino) noexcept;
	std::unique_ptr<Item> remove(std::string_view name) noexcept;
	std::unique_ptr<BrainDrainer> remove() noexcept;

	bool has(Amazon* const amazon) const noexcept;
	bool has(Dino* const dino) const noexcept;
	bool has(std::string_view name) const noexcept;
	bool has() const noexcept;

	bool spawnDino() noexcept;
	bool spawnItem(std::string_view name) noexcept;
	bool spawnDrainer() noexcept;

	const std::unordered_set<Amazon*>& AmazonContainer() const noexcept;
	const std::vector<std::unique_ptr<Dino>>& DinoContainer() const noexcept;
	const std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>>& ItemContainer() const noexcept;
	BrainDrainer* braindrainer() const noexcept;
};


class Map
{
private:
	std::vector<std::vector<Tile>> tiles;
	int sz;

public:
	Map(const int i) noexcept;
	Map(Map&&) noexcept = delete;
	
	Tile& tile(const Point p) noexcept;

	int size() const noexcept;

	Point find(Amazon* const amazon) const noexcept;
};

#endif