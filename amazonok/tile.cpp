#include "tile.h"

using namespace std;

Tile::Tile()
{
	items.emplace(ItemType::gun, vector<unique_ptr<Item>>());
}


Tile::Tile(Tile&& other) noexcept : amazons(move(other.amazons)), dinos(move(other.dinos)), items(move(other.items)) {}


bool Tile::has(string_view name)
{
	for (auto& x : items.at(ItemFactory::lookUp(name)))
		if (x->get_name() == name)
			return true;
	return false;
}


void Tile::add(unique_ptr<Item>&& item)
{
	items.at(ItemFactory::lookUp(item->get_name())).emplace_back(move(item));
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
	if (dinos.size() != 0)
		return false;

	dinos.emplace(make_unique<Dino>());
	return true;
}


bool Tile::spawnItem(string_view name)
{
	if (items.at(ItemFactory::lookUp(name)).size() != 0)
		return false;

	items.at(ItemFactory::lookUp(name)).emplace_back(ItemFactory::CreateItem(name));
	return true;
}


void Tile::place(Amazon* amazon)
{
	amazons.insert(amazon);
}


void Tile::remove(Amazon* amazon)
{
	amazons.erase(amazon);
}


bool Tile::is_here(Amazon* amazon)
{
	if (amazons.find(amazon) != amazons.end())
		return true;
	return false;
}


forward_list<Amazon*> Tile::amazon_list() const
{
	forward_list<Amazon*> ret;

	for (const auto& x : amazons)
		ret.push_front(x);

	return ret;
}


forward_list<Dino*> Tile::dino_list() const
{
	forward_list<Dino*> ret;

	for (const auto& x : dinos)
		ret.push_front(x.get());

	return ret;
}


forward_list<Item*> Tile::item_list() const
{
	forward_list<Item*> ret;;

	for (const auto& x : items)
		for (auto& y : x.second)
			ret.push_front(y.get());

	return ret;
}