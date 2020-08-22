#pragma once

#include "Amazon.h"
#include "Braindrainer.h"

#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <memory>

class Tile
{
private:
	std::unordered_set<Amazon*> m_Amazons;
	std::vector<std::unique_ptr<Dino>> m_Dinos;
	std::unordered_map<ItemType, std::vector<std::unique_ptr<Item>>> m_Items;
	std::unique_ptr<BrainDrainer> m_Braindrainer;
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