#include "tile.h"

using namespace std;

Tile::Tile()
{
	items.emplace(ItemType::gun, vector<unique_ptr<Item>>());
}


Tile::Tile(Tile&& other) noexcept : amazons(move(other.amazons)), items(move(other.items)) {}


void Tile::add(Amazon* amazon)
{
	amazons.insert(amazon);
}


void Tile::add(unique_ptr<Dino>&& dino)
{
	dinos.push_back(move(dino));
}


void Tile::add(unique_ptr<Item>&& item)
{
	items.at(ItemFactory::lookUp(item->get_name())).emplace_back(move(item));
}


void Tile::remove(Amazon* amazon)
{
	amazons.erase(amazon);
}


unique_ptr<Dino> Tile::remove(Dino* dino)
{
	for (int i = 0; i < dinos.size(); i++)
		if (dinos.at(i).get() == dino)
		{
			auto ret(move(dinos.at(i)));
			dinos.erase(dinos.begin() + i);
			return ret;
		}
}


unique_ptr<Item> Tile::remove(string_view name)
{
	for (int i = 0; i < items.at(ItemFactory::lookUp(name)).size(); i++)
		if (items.at(ItemFactory::lookUp(name)).at(i)->get_name() == name)
		{
			unique_ptr<Item> ret(move(items.at(ItemFactory::lookUp(name)).at(i)));
			items.at(ItemFactory::lookUp(name)).erase(items.at(ItemFactory::lookUp(name)).begin() + i);
			return ret;
		}
}


bool Tile::spawnDino()
{
	if (dinos.size())
		return false;

	dinos.emplace_back(make_unique<Dino>());
	return true;
}


bool Tile::spawnItem(string_view name)
{
	if (items.at(ItemFactory::lookUp(name)).size())
		return false;

	items.at(ItemFactory::lookUp(name)).emplace_back(ItemFactory::CreateItem(name));
	return true;
}


bool Tile::is_here(Amazon* const amazon)
{
	return amazons.find(amazon) != amazons.end();
}


bool Tile::is_here(Dino* const dino)
{
	for (const auto& x : dinos)
		if (x.get() == dino)
			return true;
	return false;
}


bool Tile::has(string_view name)
{
	for (const auto& x : items.at(ItemFactory::lookUp(name)))
		if (x->get_name() == name)
			return true;
	return false;
}


const unordered_set<Amazon*>& Tile::AmazonContainer() const
{
	return amazons;
}


const vector<unique_ptr<Dino>>& Tile::DinoContainer() const
{
	return dinos;
}


const unordered_map<ItemType, vector<unique_ptr<Item>>>& Tile::ItemContainer() const
{
	return items;
}