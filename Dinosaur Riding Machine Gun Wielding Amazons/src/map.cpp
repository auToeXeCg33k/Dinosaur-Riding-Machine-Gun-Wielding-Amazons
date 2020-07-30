#include <random>

#include "map.h"

using std::unique_ptr;
using std::vector;
using std::string_view;
using std::make_unique;
using std::uniform_int_distribution;


Tile::Tile() noexcept
{
	items.emplace(ItemType::gun, vector<unique_ptr<Item>>());
}


Tile::Tile(Tile&& other) noexcept : amazons(move(other.amazons)), dinos(move(other.dinos)), items(move(other.items)), drainer(move(other.drainer)) {}


void Tile::add(Amazon* const amazon) noexcept
{
	amazons.insert(amazon);
}


void Tile::add(unique_ptr<Dino>&& dino) noexcept
{
	dinos.push_back(move(dino));
}


void Tile::add(unique_ptr<Item>&& item) noexcept
{
	items.at(ItemFactory::lookUp(item->name())).emplace_back(move(item));
}


void Tile::add(unique_ptr<BrainDrainer>&& drainer) noexcept
{
	this->drainer = move(drainer);
}


void Tile::remove(Amazon* const amazon) noexcept
{
	amazons.erase(amazon);
}


unique_ptr<Dino> Tile::remove(Dino* dino) noexcept
{
	for (size_t i = 0; i < dinos.size(); i++)
		if (dinos.at(i).get() == dino)
		{
			auto ret(move(dinos.at(i)));
			dinos.erase(dinos.begin() + i);
			return ret;
		}
}


unique_ptr<Item> Tile::remove(string_view name) noexcept
{
	for (size_t i = 0; i < items.at(ItemFactory::lookUp(name)).size(); i++)
		if (items.at(ItemFactory::lookUp(name)).at(i)->name() == name)
		{
			unique_ptr<Item> ret(move(items.at(ItemFactory::lookUp(name)).at(i)));
			items.at(ItemFactory::lookUp(name)).erase(items.at(ItemFactory::lookUp(name)).begin() + i);
			return ret;
		}
}


unique_ptr<BrainDrainer> Tile::remove() noexcept
{
	return move(drainer);
}


bool Tile::has(Amazon* const amazon) const noexcept
{
	return amazons.find(amazon) != amazons.end();
}


bool Tile::has(Dino* const dino) const noexcept
{
	for (const auto& x : dinos)
		if (x.get() == dino)
			return true;
	return false;
}


bool Tile::has(string_view name) const noexcept
{
	for (const auto& x : items.at(ItemFactory::lookUp(name)))
		if (x->name() == name)
			return true;
	return false;
}


bool Tile::has() const noexcept
{
	return drainer.get();
}


bool Tile::spawnDino() noexcept
{
	if (dinos.size())
		return false;

	dinos.emplace_back(make_unique<Dino>());
	return true;
}


bool Tile::spawnItem(string_view name) noexcept
{
	if (items.at(ItemFactory::lookUp(name)).size())
		return false;

	items.at(ItemFactory::lookUp(name)).emplace_back(ItemFactory::createItem(name));
	return true;
}


bool Tile::spawnDrainer() noexcept
{
	if (drainer)
		return false;

	drainer = make_unique<BrainDrainer>();
	return true;
}


const std::unordered_set<Amazon*>& Tile::AmazonContainer() const noexcept
{
	return amazons;
}


const vector<unique_ptr<Dino>>& Tile::DinoContainer() const noexcept
{
	return dinos;
}


const std::unordered_map<ItemType, vector<unique_ptr<Item>>>& Tile::ItemContainer() const noexcept
{
	return items;
}


BrainDrainer* Tile::braindrainer() const noexcept
{
	return drainer.get();
}




Map::Map(const int i) noexcept
{
	switch (i)
	{
	case 1:
		sz = 5;
		for (int i = 0; i < 5; i++)
		{
			tiles.emplace_back();
			for (int j = 0; j < 5; j++)
				tiles.at(i).emplace_back();
		}

		std::random_device rd;
		std::mt19937_64 mt(rd());

		uniform_int_distribution<> dist1(0, 4);

		for (int i = 0; i < 5; i++)
			while (!tiles.at(dist1(mt)).at(dist1(mt)).spawnDino());

		for (int i = 0; i < 2; i++)
		{
			while (!tiles.at(0).at(dist1(mt)).spawnItem("pistol"));
			while (!tiles.at(4).at(dist1(mt)).spawnItem("pistol"));
		}

		uniform_int_distribution<unsigned> dist2(0, 1);

		while (!tiles.at(dist2(mt)).at(dist1(mt)).spawnItem("shotgun"));
		while (!tiles.at(4 - dist2(mt)).at(dist1(mt)).spawnItem("shotgun"));
		while (!tiles.at(dist1(mt)).at(dist1(mt)).spawnItem("katana"));
		while (!tiles.at(2).at(dist1(mt)).spawnItem("minigun"));

		uniform_int_distribution<unsigned> dist3(0,2);

		for (int i = 0; i < 2; i++)
			while (!tiles.at(3 - dist3(mt)).at(dist1(mt)).spawnDrainer());

		return;
	}
}


Tile& Map::tile(const Point p) noexcept
{
	return tiles.at(p.y()).at(p.x());
}


int Map::size() const noexcept
{
	return sz;
}


Point Map::find(Amazon* amazon) const noexcept
{
	for (int i = 0; i < sz; i++)
		for (int j = 0; j < sz; j++)
			if (tiles.at(i).at(j).has(amazon))
				return Point(j, i);
}